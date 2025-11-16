#include <vector>
#include <mutex>

namespace circular_buffer {

template <typename T>
class CircularBuffer {
public:
    explicit CircularBuffer(size_t capacity)
        : buffer_(capacity), capacity_(capacity), head_(0), tail_(0), size_(0) {}

    void push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        buffer_[head_] = item;
        head_ = (head_ + 1) % capacity_;
        if (size_ < capacity_) {
            ++size_;
        } else {
            tail_ = (tail_ + 1) % capacity_;
        }
    }

    bool pop(T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (size_ == 0) {
            return false;
        }
        item = buffer_[tail_];
        tail_ = (tail_ + 1) % capacity_;
        --size_;
        return true;
    }

    bool peek(T& item) const {
        std::lock_guard<std::mutex> lock(mutex_);
        if (size_ == 0) {
            return false;
        }
        item = buffer_[tail_];
        return true;
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return size_;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return size_ == 0;
    }

    bool full() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return size_ == capacity_;
    }

private:
    mutable std::mutex mutex_;
    std::vector<T> buffer_;
    size_t capacity_;
    size_t head_;
    size_t tail_;
    size_t size_;
};

}  // namespace circular_buffer