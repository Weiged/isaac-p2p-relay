#ifndef PLATFORM_WIN_H
#define PLATFORM_WIN_H

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <ws2tcpip.h>

namespace p2p {

using SocketHandle = SOCKET;
constexpr SocketHandle INVALID_SOCKET_HANDLE = INVALID_SOCKET;

inline int getLastError() {
    return WSAGetLastError();
}

inline void closeSocket(SocketHandle sock) {
    if (sock != INVALID_SOCKET_HANDLE) {
        closesocket(sock);
    }
}

inline bool setNonBlocking(SocketHandle sock) {
    u_long mode = 1;
    return ioctlsocket(sock, FIONBIO, &mode) == 0;
}

inline bool setReuseAddr(SocketHandle sock) {
    int opt = 1;
    return setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, 
                      reinterpret_cast<const char*>(&opt), sizeof(opt)) == 0;
}

inline bool setNoDelay(SocketHandle sock) {
    int opt = 1;
    return setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,
                      reinterpret_cast<const char*>(&opt), sizeof(opt)) == 0;
}

inline bool wouldBlock() {
    int err = WSAGetLastError();
    return err == WSAEWOULDBLOCK || err == WSAEINPROGRESS;
}

inline bool initializeSockets() {
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
}

inline void cleanupSockets() {
    WSACleanup();
}

} // namespace p2p

#endif // _WIN32

#endif // PLATFORM_WIN_H
