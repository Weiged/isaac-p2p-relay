#ifndef PACKET_QUEUE_H
#define PACKET_QUEUE_H

#include <vector>
#include <queue>
#include <cstdint>
#include <mutex>

namespace p2p {

/**
 * 数据包结构
 */
struct Packet {
    std::vector<uint8_t> data;
    
    Packet() = default;
    explicit Packet(const void* src, uint32_t size) 
        : data(static_cast<const uint8_t*>(src), static_cast<const uint8_t*>(src) + size) {}
    
    Packet(Packet&&) noexcept = default;
    Packet& operator=(Packet&&) noexcept = default;
    
    Packet(const Packet&) = default;
    Packet& operator=(const Packet&) = default;
    
    uint32_t size() const { return static_cast<uint32_t>(data.size()); }
    bool empty() const { return data.empty(); }
};

/**
 * 数据包队列 - 用于存储接收到的完整数据包
 */
class PacketQueue {
public:
    PacketQueue() = default;
    ~PacketQueue() = default;
    
    // 禁止拷贝
    PacketQueue(const PacketQueue&) = delete;
    PacketQueue& operator=(const PacketQueue&) = delete;
    
    // 移动构造/赋值 (mutex 不能移动，但队列内容可以)
    PacketQueue(PacketQueue&& other) noexcept {
        std::lock_guard<std::mutex> lock(other.m_mutex);
        m_queue = std::move(other.m_queue);
    }
    
    PacketQueue& operator=(PacketQueue&& other) noexcept {
        if (this != &other) {
            std::scoped_lock lock(m_mutex, other.m_mutex);
            m_queue = std::move(other.m_queue);
        }
        return *this;
    }
    
    /**
     * 将数据包加入队列
     * @param packet 数据包
     */
    void push(Packet&& packet);
    
    /**
     * 将数据加入队列
     * @param data 数据指针
     * @param size 数据大小
     */
    void push(const void* data, uint32_t size);
    
    /**
     * 弹出队首数据包
     * @param outPacket 输出数据包
     * @return true 成功, false 队列为空
     */
    bool pop(Packet& outPacket);
    
    /**
     * 查看队首数据包大小 (不移除)
     * @param outSize 输出大小
     * @return true 有数据包, false 队列为空
     */
    bool peek(uint32_t& outSize) const;
    
    /**
     * 检查队列是否为空
     */
    bool empty() const;
    
    /**
     * 获取队列中数据包数量
     */
    size_t size() const;
    
    /**
     * 清空队列
     */
    void clear();

private:
    std::queue<Packet> m_queue;
    mutable std::mutex m_mutex;
};

/**
 * 接收缓冲区 - 用于从 TCP 流中解析完整数据包
 * 数据包格式: [4字节长度][数据内容]
 */
class ReceiveBuffer {
public:
    ReceiveBuffer() = default;
    ~ReceiveBuffer() = default;
    
    /**
     * 追加接收到的原始数据
     * @param data 数据指针
     * @param size 数据大小
     */
    void append(const void* data, uint32_t size);
    
    /**
     * 尝试从缓冲区中解析出完整数据包
     * @param outPacket 输出数据包
     * @return true 解析成功, false 数据不完整
     */
    bool tryParsePacket(Packet& outPacket);
    
    /**
     * 获取缓冲区大小
     */
    size_t size() const { return m_buffer.size(); }
    
    /**
     * 清空缓冲区
     */
    void clear() { m_buffer.clear(); }

private:
    std::vector<uint8_t> m_buffer;
    
    static constexpr uint32_t HEADER_SIZE = 4;  // 包头大小 (4字节长度)
    static constexpr uint32_t MAX_PACKET_SIZE = 1024 * 1024;  // 最大包大小 1MB
};

} // namespace p2p

#endif // PACKET_QUEUE_H
