#include "connection_manager.h"
#include <cstring>
#include <algorithm>

namespace p2p {

ConnectionManager::ConnectionManager() = default;

ConnectionManager::~ConnectionManager() {
    shutdown();
}

bool ConnectionManager::initialize() {
    if (m_initialized) {
        return true;
    }
    
    if (!initializeSockets()) {
        return false;
    }
    
    m_initialized = true;
    return true;
}

void ConnectionManager::shutdown() {
    if (!m_initialized) {
        return;
    }
    
    // 关闭监听 socket
    stopListen();
    
    // 关闭所有连接
    for (auto& [peerID, conn] : m_connections) {
        closeSocket(conn.socket);
    }
    m_connections.clear();
    m_pendingRemove.clear();
    
    cleanupSockets();
    m_initialized = false;
}

bool ConnectionManager::listen(uint16_t port) {
    if (!m_initialized) {
        return false;
    }
    
    // 如果已经在监听，先停止
    stopListen();
    
    // 创建监听 socket
    m_listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_listenSocket == INVALID_SOCKET_HANDLE) {
        return false;
    }
    
    // 设置 socket 选项
    setReuseAddr(m_listenSocket);
    setNonBlocking(m_listenSocket);
    
    // 绑定地址
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    
    if (bind(m_listenSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0) {
        closeSocket(m_listenSocket);
        m_listenSocket = INVALID_SOCKET_HANDLE;
        return false;
    }
    
    // 开始监听
    if (::listen(m_listenSocket, SOMAXCONN) != 0) {
        closeSocket(m_listenSocket);
        m_listenSocket = INVALID_SOCKET_HANDLE;
        return false;
    }
    
    m_listenPort = port;
    return true;
}

void ConnectionManager::stopListen() {
    if (m_listenSocket != INVALID_SOCKET_HANDLE) {
        closeSocket(m_listenSocket);
        m_listenSocket = INVALID_SOCKET_HANDLE;
        m_listenPort = 0;
    }
}

bool ConnectionManager::connect(const char* ip, uint16_t port, P2PPeerID& outPeerID) {
    if (!m_initialized || !ip) {
        return false;
    }
    
    // 创建 socket
    SocketHandle sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET_HANDLE) {
        return false;
    }
    
    // 设置 socket 选项
    setNoDelay(sock);
    
    // 解析地址
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, ip, &addr.sin_addr) != 1) {
        closeSocket(sock);
        return false;
    }
    
    // 同步连接 (简化实现)
    if (::connect(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0) {
        closeSocket(sock);
        return false;
    }
    
    // 连接成功后设置为非阻塞
    setNonBlocking(sock);
    
    // 分配 PeerID 并创建连接
    P2PPeerID peerID = allocatePeerID();
    
    Connection conn;
    conn.socket = sock;
    conn.peerID = peerID;
    conn.remoteIP = ip;
    conn.remotePort = port;
    conn.connected = true;
    
    m_connections.emplace(peerID, std::move(conn));
    
    outPeerID = peerID;
    
    // 通知连接事件
    notifyConnectionEvent(peerID, ConnectionEvent::Connected);
    
    return true;
}

void ConnectionManager::disconnect(P2PPeerID peerID) {
    auto it = m_connections.find(peerID);
    if (it == m_connections.end()) {
        return;
    }
    
    closeSocket(it->second.socket);
    
    // 通知断开事件
    notifyConnectionEvent(peerID, ConnectionEvent::Disconnected);
    
    m_connections.erase(it);
}

bool ConnectionManager::sendPacket(P2PPeerID peerID, const void* data, uint32_t size) {
    if (!data || size == 0) {
        return false;
    }
    
    auto it = m_connections.find(peerID);
    if (it == m_connections.end() || !it->second.connected) {
        return false;
    }
    
    Connection& conn = it->second;
    
    // 创建发送帧 (4字节长度头 + 数据)
    std::vector<uint8_t> frame = createSendFrame(data, size);
    
    // 尝试立即发送
    int sent = send(conn.socket, reinterpret_cast<const char*>(frame.data()), 
                    static_cast<int>(frame.size()), 0);
    
    if (sent < 0) {
        if (wouldBlock()) {
            // 缓冲区满，加入发送队列
            conn.sendBuffer.insert(conn.sendBuffer.end(), frame.begin(), frame.end());
            return true;
        }
        // 发送错误，标记断开
        conn.connected = false;
        m_pendingRemove.push_back(peerID);
        return false;
    }
    
    // 部分发送，剩余数据加入队列
    if (static_cast<size_t>(sent) < frame.size()) {
        conn.sendBuffer.insert(conn.sendBuffer.end(), 
                               frame.begin() + sent, frame.end());
    }
    
    return true;
}

bool ConnectionManager::isPacketAvailable(P2PPeerID peerID, uint32_t* outSize, P2PPeerID* outPeerID) {
    if (peerID != P2P_INVALID_PEER_ID) {
        // 检查指定连接
        auto it = m_connections.find(peerID);
        if (it == m_connections.end()) {
            return false;
        }
        
        uint32_t size = 0;
        if (it->second.receiveQueue.peek(size)) {
            if (outSize) *outSize = size;
            if (outPeerID) *outPeerID = peerID;
            return true;
        }
        return false;
    }
    
    // 检查所有连接
    for (auto& [pid, conn] : m_connections) {
        uint32_t size = 0;
        if (conn.receiveQueue.peek(size)) {
            if (outSize) *outSize = size;
            if (outPeerID) *outPeerID = pid;
            return true;
        }
    }
    
    return false;
}

bool ConnectionManager::readPacket(P2PPeerID peerID, void* buffer, uint32_t bufferSize,
                                   uint32_t* outReadSize, P2PPeerID* outPeerID) {
    if (!buffer || bufferSize == 0) {
        return false;
    }
    
    Connection* conn = nullptr;
    P2PPeerID sourcePeerID = P2P_INVALID_PEER_ID;
    
    if (peerID != P2P_INVALID_PEER_ID) {
        // 从指定连接读取
        auto it = m_connections.find(peerID);
        if (it == m_connections.end()) {
            return false;
        }
        conn = &it->second;
        sourcePeerID = peerID;
    } else {
        // 从任意连接读取
        for (auto& [pid, c] : m_connections) {
            uint32_t size = 0;
            if (c.receiveQueue.peek(size)) {
                conn = &c;
                sourcePeerID = pid;
                break;
            }
        }
    }
    
    if (!conn) {
        return false;
    }
    
    // 弹出数据包
    Packet packet;
    if (!conn->receiveQueue.pop(packet)) {
        return false;
    }
    
    // 检查缓冲区大小
    if (packet.size() > bufferSize) {
        // 缓冲区太小，数据包丢失
        return false;
    }
    
    // 复制数据
    std::memcpy(buffer, packet.data.data(), packet.size());
    
    if (outReadSize) *outReadSize = packet.size();
    if (outPeerID) *outPeerID = sourcePeerID;
    
    return true;
}

void ConnectionManager::processEvents() {
    if (!m_initialized) {
        return;
    }
    
    // 接受新连接
    acceptNewConnections();
    
    // 处理现有连接
    fd_set readSet, writeSet, exceptSet;
    FD_ZERO(&readSet);
    FD_ZERO(&writeSet);
    FD_ZERO(&exceptSet);
    
    SocketHandle maxFd = 0;
    
    for (auto& [peerID, conn] : m_connections) {
        if (conn.socket != INVALID_SOCKET_HANDLE && conn.connected) {
            FD_SET(conn.socket, &readSet);
            FD_SET(conn.socket, &exceptSet);
            
            // 如果有待发送数据，监听写事件
            if (!conn.sendBuffer.empty()) {
                FD_SET(conn.socket, &writeSet);
            }
            
            if (conn.socket > maxFd) {
                maxFd = conn.socket;
            }
        }
    }
    
    if (maxFd == 0 && m_connections.empty()) {
        removeDisconnected();
        return;
    }
    
    // 非阻塞 select
    timeval timeout{};
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    
    int result = select(static_cast<int>(maxFd + 1), &readSet, &writeSet, &exceptSet, &timeout);
    
    if (result > 0) {
        for (auto& [peerID, conn] : m_connections) {
            if (conn.socket == INVALID_SOCKET_HANDLE || !conn.connected) {
                continue;
            }
            
            // 检查异常
            if (FD_ISSET(conn.socket, &exceptSet)) {
                conn.connected = false;
                m_pendingRemove.push_back(peerID);
                continue;
            }
            
            // 处理读取
            if (FD_ISSET(conn.socket, &readSet)) {
                processRead(conn);
            }
            
            // 处理写入
            if (FD_ISSET(conn.socket, &writeSet)) {
                processWrite(conn);
            }
        }
    }
    
    // 移除断开的连接
    removeDisconnected();
}

void ConnectionManager::setConnectionCallback(ConnectionCallback callback) {
    m_connectionCallback = std::move(callback);
}

uint32_t ConnectionManager::getPeerCount() const {
    return static_cast<uint32_t>(m_connections.size());
}

uint32_t ConnectionManager::getConnectedPeers(P2PPeerID* outPeerIDs, uint32_t maxCount) const {
    if (!outPeerIDs || maxCount == 0) {
        return 0;
    }
    
    uint32_t count = 0;
    for (const auto& [peerID, conn] : m_connections) {
        if (conn.connected && count < maxCount) {
            outPeerIDs[count++] = peerID;
        }
    }
    
    return count;
}

P2PPeerID ConnectionManager::allocatePeerID() {
    return m_nextPeerID++;
}

void ConnectionManager::acceptNewConnections() {
    if (m_listenSocket == INVALID_SOCKET_HANDLE) {
        return;
    }
    
    while (true) {
        sockaddr_in clientAddr{};
        int addrLen = sizeof(clientAddr);
        
        SocketHandle clientSocket = accept(m_listenSocket, 
                                           reinterpret_cast<sockaddr*>(&clientAddr),
                                           &addrLen);
        
        if (clientSocket == INVALID_SOCKET_HANDLE) {
            break;  // 没有更多连接
        }
        
        // 设置 socket 选项
        setNonBlocking(clientSocket);
        setNoDelay(clientSocket);
        
        // 获取客户端 IP
        char ipStr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, ipStr, sizeof(ipStr));
        
        // 分配 PeerID
        P2PPeerID peerID = allocatePeerID();
        
        Connection conn;
        conn.socket = clientSocket;
        conn.peerID = peerID;
        conn.remoteIP = ipStr;
        conn.remotePort = ntohs(clientAddr.sin_port);
        conn.connected = true;
        
        m_connections.emplace(peerID, std::move(conn));
        
        // 通知新连接
        notifyConnectionEvent(peerID, ConnectionEvent::Connected);
    }
}

void ConnectionManager::processRead(Connection& conn) {
    char buffer[RECV_BUFFER_SIZE];
    
    while (true) {
        int received = recv(conn.socket, buffer, sizeof(buffer), 0);
        
        if (received > 0) {
            // 追加到接收缓冲区
            conn.recvBuffer.append(buffer, static_cast<uint32_t>(received));
            
            // 尝试解析完整数据包
            Packet packet;
            while (conn.recvBuffer.tryParsePacket(packet)) {
                conn.receiveQueue.push(std::move(packet));
            }
        } else if (received == 0) {
            // 连接正常关闭
            conn.connected = false;
            m_pendingRemove.push_back(conn.peerID);
            break;
        } else {
            if (wouldBlock()) {
                // 没有更多数据
                break;
            }
            // 读取错误
            conn.connected = false;
            m_pendingRemove.push_back(conn.peerID);
            break;
        }
    }
}

void ConnectionManager::processWrite(Connection& conn) {
    if (conn.sendBuffer.empty()) {
        return;
    }
    
    int sent = send(conn.socket, 
                    reinterpret_cast<const char*>(conn.sendBuffer.data()),
                    static_cast<int>(conn.sendBuffer.size()), 0);
    
    if (sent > 0) {
        conn.sendBuffer.erase(conn.sendBuffer.begin(), 
                              conn.sendBuffer.begin() + sent);
    } else if (sent < 0 && !wouldBlock()) {
        // 发送错误
        conn.connected = false;
        m_pendingRemove.push_back(conn.peerID);
    }
}

void ConnectionManager::removeDisconnected() {
    // 去重
    std::sort(m_pendingRemove.begin(), m_pendingRemove.end());
    m_pendingRemove.erase(std::unique(m_pendingRemove.begin(), m_pendingRemove.end()),
                          m_pendingRemove.end());
    
    for (P2PPeerID peerID : m_pendingRemove) {
        auto it = m_connections.find(peerID);
        if (it != m_connections.end()) {
            closeSocket(it->second.socket);
            notifyConnectionEvent(peerID, ConnectionEvent::Disconnected);
            m_connections.erase(it);
        }
    }
    
    m_pendingRemove.clear();
}

void ConnectionManager::notifyConnectionEvent(P2PPeerID peerID, ConnectionEvent event) {
    if (m_connectionCallback) {
        m_connectionCallback(peerID, event);
    }
}

std::vector<uint8_t> ConnectionManager::createSendFrame(const void* data, uint32_t size) {
    std::vector<uint8_t> frame;
    frame.reserve(4 + size);
    
    // 写入长度头 (小端序)
    frame.push_back(static_cast<uint8_t>(size & 0xFF));
    frame.push_back(static_cast<uint8_t>((size >> 8) & 0xFF));
    frame.push_back(static_cast<uint8_t>((size >> 16) & 0xFF));
    frame.push_back(static_cast<uint8_t>((size >> 24) & 0xFF));
    
    // 写入数据
    const uint8_t* bytes = static_cast<const uint8_t*>(data);
    frame.insert(frame.end(), bytes, bytes + size);
    
    return frame;
}

} // namespace p2p
