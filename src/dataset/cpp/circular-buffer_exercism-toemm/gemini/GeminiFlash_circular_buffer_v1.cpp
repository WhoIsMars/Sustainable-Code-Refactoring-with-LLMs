#include "circular_buffer.h"
#include <algorithm>
#include <stdexcept>

namespace circular_buffer {

circular_buffer::circular_buffer(size_t capacity) : capacity_(capacity), buffer_(new int[capacity]), head_(0), tail_(0), size_(0) {
    if (capacity == 0) {
        throw std::invalid_argument("Circular buffer capacity must be greater than zero.");
    }
}

circular_buffer::~circular_buffer() {
    delete[] buffer_;
}

int circular_buffer::push(int value) {
    if (is_full()) {
        tail_ = (tail_ + 1) % capacity_;
    } else {
        size_++;
    }
    buffer_[head_] = value;
    head_ = (head_ + 1) % capacity_;
    return value;
}

int circular_buffer::pop() {
    if (is_empty()) {
        throw std::out_of_range("Circular buffer is empty.");
    }
    int value = buffer_[tail_];
    tail_ = (tail_ + 1) % capacity_;
    size_--;
    return value;
}

int circular_buffer::front() const {
    if (is_empty()) {
        throw std::out_of_range("Circular buffer is empty.");
    }
    return buffer_[tail_];
}

int circular_buffer::back() const {
    if (is_empty()) {
        throw std::out_of_range("Circular buffer is empty.");
    }
    return buffer_[(head_ == 0 ? capacity_ : head_) - 1];
}

size_t circular_buffer::size() const {
    return size_;
}

size_t circular_buffer::capacity() const {
    return capacity_;
}

bool circular_buffer::is_empty() const {
    return size_ == 0;
}

bool circular_buffer::is_full() const {
    return size_ == capacity_;
}

void circular_buffer::clear() {
    head_ = 0;
    tail_ = 0;
    size_ = 0;
}

circular_buffer::circular_buffer(const circular_buffer& other) : capacity_(other.capacity_), buffer_(new int[other.capacity_]), head_(other.head_), tail_(other.tail_), size_(other.size_) {
    std::copy(other.buffer_, other.buffer_ + capacity_, buffer_);
}

circular_buffer& circular_buffer::operator=(const circular_buffer& other) {
    if (this != &other) {
        if (capacity_ != other.capacity_) {
            delete[] buffer_;
            capacity_ = other.capacity_;
            buffer_ = new int[capacity_];
        }
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        std::copy(other.buffer_, other.buffer_ + capacity_, buffer_);
    }
    return *this;
}

circular_buffer::circular_buffer(circular_buffer&& other) noexcept : capacity_(other.capacity_), buffer_(other.buffer_), head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.buffer_ = nullptr;
    other.capacity_ = 0;
    other.head_ = 0;
    other.tail_ = 0;
    other.size_ = 0;
}

circular_buffer& circular_buffer::operator=(circular_buffer&& other) noexcept {
    if (this != &other) {
        delete[] buffer_;
        capacity_ = other.capacity_;
        buffer_ = other.buffer_;
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;

        other.buffer_ = nullptr;
        other.capacity_ = 0;
        other.head_ = 0;
        other.tail_ = 0;
        other.size_ = 0;
    }
    return *this;
}

}  // namespace circular_buffer