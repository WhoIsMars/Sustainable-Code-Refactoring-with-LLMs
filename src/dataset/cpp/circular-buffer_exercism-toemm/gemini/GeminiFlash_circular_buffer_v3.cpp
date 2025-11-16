#include "circular_buffer.h"
#include <algorithm>
#include <stdexcept>
#include <cstring> // For memcpy

namespace circular_buffer {

template <typename T>
CircularBuffer<T>::CircularBuffer(size_t capacity) : capacity_(capacity), size_(0), head_(0), tail_(0) {
  if (capacity == 0) {
    throw std::invalid_argument("Capacity must be greater than zero.");
  }
  buffer_ = std::unique_ptr<T[]>(new T[capacity_]);
}

template <typename T>
bool CircularBuffer<T>::empty() const {
  return size_ == 0;
}

template <typename T>
bool CircularBuffer<T>::full() const {
  return size_ == capacity_;
}

template <typename T>
size_t CircularBuffer<T>::size() const {
  return size_;
}

template <typename T>
size_t CircularBuffer<T>::capacity() const {
  return capacity_;
}

template <typename T>
void CircularBuffer<T>::push_back(const T& value) {
  if (full()) {
    throw std::overflow_error("Circular buffer is full.");
  }

  buffer_[tail_] = value;
  tail_ = (tail_ + 1) % capacity_;
  ++size_;
}

template <typename T>
void CircularBuffer<T>::push_back(T&& value) {
  if (full()) {
    throw std::overflow_error("Circular buffer is full.");
  }

  buffer_[tail_] = std::move(value);
  tail_ = (tail_ + 1) % capacity_;
  ++size_;
}

template <typename T>
void CircularBuffer<T>::pop_front() {
  if (empty()) {
    throw std::underflow_error("Circular buffer is empty.");
  }

  head_ = (head_ + 1) % capacity_;
  --size_;
}

template <typename T>
T& CircularBuffer<T>::front() {
  if (empty()) {
    throw std::underflow_error("Circular buffer is empty.");
  }
  return buffer_[head_];
}

template <typename T>
const T& CircularBuffer<T>::front() const {
  if (empty()) {
    throw std::underflow_error("Circular buffer is empty.");
  }
  return buffer_[head_];
}

template <typename T>
T& CircularBuffer<T>::back() {
  if (empty()) {
    throw std::underflow_error("Circular buffer is empty.");
  }
  return buffer_[(tail_ + capacity_ - 1) % capacity_];
}

template <typename T>
const T& CircularBuffer<T>::back() const {
  if (empty()) {
    throw std::underflow_error("Circular buffer is empty.");
  }
  return buffer_[(tail_ + capacity_ - 1) % capacity_];
}

template <typename T>
void CircularBuffer<T>::clear() {
  head_ = 0;
  tail_ = 0;
  size_ = 0;
}

template <typename T>
T& CircularBuffer<T>::operator[](size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return buffer_[(head_ + index) % capacity_];
}

template <typename T>
const T& CircularBuffer<T>::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return buffer_[(head_ + index) % capacity_];
}

}  // namespace circular_buffer