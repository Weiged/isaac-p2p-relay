#include "packet_queue.h"
#include <cstring>
#include <algorithm>

namespace p2p {

// ============================================================================
// PacketQueue 实现
// ============================================================================

void PacketQueue::push(Packet&& packet) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.push(std::move(packet));
}

void PacketQueue::push(const void* data, uint32_t size) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.emplace(data, size);
}

bool PacketQueue::pop(Packet& outPacket) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_queue.empty()) {
        return false;
    }
    outPacket = std::move(m_queue.front());
    m_queue.pop();
    return true;
}

bool PacketQueue::peek(uint32_t& outSize) const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_queue.empty()) {
        return false;
    }
    outSize = m_queue.front().size();
    return true;
}

bool PacketQueue::empty() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.empty();
}

size_t PacketQueue::size() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.size();
}

void PacketQueue::clear() {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::queue<Packet> empty;
    std::swap(m_queue, empty);
}

// ============================================================================
// ReceiveBuffer 实现
// ============================================================================

void ReceiveBuffer::append(const void* data, uint32_t size) {
    const uint8_t* bytes = static_cast<const uint8_t*>(data);
    m_buffer.insert(m_buffer.end(), bytes, bytes + size);
}

bool ReceiveBuffer::tryParsePacket(Packet& outPacket) {
    // 检查是否有足够的数据来读取包头
    if (m_buffer.size() < HEADER_SIZE) {
        return false;
    }
    
    // 读取包长度 (小端序)
    uint32_t packetSize = 0;
    packetSize |= static_cast<uint32_t>(m_buffer[0]);
    packetSize |= static_cast<uint32_t>(m_buffer[1]) << 8;
    packetSize |= static_cast<uint32_t>(m_buffer[2]) << 16;
    packetSize |= static_cast<uint32_t>(m_buffer[3]) << 24;
    
    // 检查包大小是否合法
    if (packetSize == 0 || packetSize > MAX_PACKET_SIZE) {
        // 包大小异常，清空缓冲区
        m_buffer.clear();
        return false;
    }
    
    // 检查是否有完整的数据包
    uint32_t totalSize = HEADER_SIZE + packetSize;
    if (m_buffer.size() < totalSize) {
        return false;
    }
    
    // 提取数据包内容
    outPacket.data.assign(
        m_buffer.begin() + HEADER_SIZE,
        m_buffer.begin() + totalSize
    );
    
    // 从缓冲区中移除已解析的数据
    m_buffer.erase(m_buffer.begin(), m_buffer.begin() + totalSize);
    
    return true;
}

} // namespace p2p
