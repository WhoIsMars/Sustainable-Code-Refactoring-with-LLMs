#include "linked_list.h"
#include <algorithm>
#include <memory>
#include <stdexcept>

namespace linked_list {

    list::list() : head_(nullptr), tail_(nullptr), count_(0) {}

    list::~list() {
        clear();
    }

    void list::push_back(int data) {
        auto newNode = std::make_unique<node>(data);
        node* rawNode = newNode.get();

        if (empty()) {
            head_ = rawNode;
            tail_ = rawNode;
        } else {
            tail_->next = rawNode;
            tail_ = rawNode;
        }

        nodes_.push_back(std::move(newNode));
        ++count_;
    }

    int list::pop_back() {
        if (empty()) {
            throw std::out_of_range("Cannot pop from an empty list");
        }

        int data = tail_->data;

        if (head_ == tail_) {
            clear();
            return data;
        }

        node* newTail = head_;
        while (newTail->next != tail_) {
            newTail = newTail->next;
        }

        tail_ = newTail;
        tail_->next = nullptr;

        // Remove from nodes_ vector
        for (auto it = nodes_.begin(); it != nodes_.end(); ++it) {
            if (it->get() == tail_->next) {
                nodes_.erase(it);
                break;
            }
        }

        --count_;
        return data;
    }

    void list::push_front(int data) {
        auto newNode = std::make_unique<node>(data);
        node* rawNode = newNode.get();

        if (empty()) {
            head_ = rawNode;
            tail_ = rawNode;
        } else {
            rawNode->next = head_;
            head_ = rawNode;
        }

        nodes_.push_back(std::move(newNode));
        std::rotate(nodes_.begin(), nodes_.end() - 1, nodes_.end()); // Maintain order for pop_back
        ++count_;
    }

    int list::pop_front() {
        if (empty()) {
            throw std::out_of_range("Cannot pop from an empty list");
        }

        int data = head_->data;

        if (head_ == tail_) {
            clear();
            return data;
        }

        head_ = head_->next;

        // Remove from nodes_ vector
        for (auto it = nodes_.begin(); it != nodes_.end(); ++it) {
            if (it->get() == head_->prev) {
                nodes_.erase(it);
                break;
            }
        }

        --count_;
        return data;
    }

    bool list::empty() const {
        return count_ == 0;
    }

    size_t list::size() const {
        return count_;
    }

    void list::clear() {
        nodes_.clear();
        head_ = nullptr;
        tail_ = nullptr;
        count_ = 0;
    }
}  // namespace linked_list