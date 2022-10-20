#ifndef OS_BUFFERED_CHANNEL_H
#define OS_BUFFERED_CHANNEL_H

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

template<class T>
class BufferedChannel {
public:
    explicit BufferedChannel(int size) : buffer_size(size), isClosed(false) {}

    void Send(T value) {
        if (isClosed) {
            throw new std::runtime_error("Channel is closed");
        }
        std::unique_lock <std::mutex> lock(mutex);
        condition.wait(lock, [this]() { return channel.size() < buffer_size; });
        channel.push(value);
        condition.notify_one();
    }

    std::pair<T, bool> Recv() {
        if (isClosed) {
            return {T(), false};
        }
        std::unique_lock <std::mutex> lock(mutex);
        condition.wait(lock, [this]() { return !channel.empty(); });
        T value = channel.front();
        channel.pop();
        condition.notify_one();
        return std::pair<T, bool>(value, true);
    }

    void Close() {
        isClosed = true;
        condition.notify_all();
    }

private:
    int buffer_size;
    bool isClosed;
    std::queue <T> channel;
    std::mutex mutex;
    std::condition_variable condition;
};

#endif //OS_BUFFERED_CHANNEL_H
