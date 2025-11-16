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

int circular_buffer::read() {
    if (empty()) {
        throw std::out_of_range("Circular buffer is empty.");
    }
    int value = buffer_[head_];
    head_ = (head_ + 1) % capacity_;
    --size_;
    return value;
}

void circular_buffer::write(int value) {
    if (full()) {
        head_ = (head_ + 1) % capacity_;
    } else {
        ++size_;
    }
    buffer_[tail_] = value;
    tail_ = (tail_ + 1) % capacity_;
}

void circular_buffer::overwrite(int value) {
    write(value);
}


void circular_buffer::clear() {
    head_ = 0;
    tail_ = 0;
    size_ = 0;
}

size_t circular_buffer::size() const {
    return size_;
}

size_t circular_buffer::capacity() const {
    return capacity_;
}

bool circular_buffer::empty() const {
    return size_ == 0;
}

bool circular_buffer::full() const {
    return size_ == capacity_;
}

}  // namespace circular_buffer