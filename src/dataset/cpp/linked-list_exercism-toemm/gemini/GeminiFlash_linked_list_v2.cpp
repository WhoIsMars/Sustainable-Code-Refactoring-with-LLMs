#include "linked_list.h"
#include <algorithm> // for std::swap
#include <stdexcept> // for std::out_of_range

namespace linked_list {

    node::node(int data, node* next) : data(data), next(next) {}

    list::list() : head(nullptr), tail(nullptr), count(0) {}

    list::~list() {
        while (head) {
            node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    int list::size() const {
        return count;
    }

    bool list::empty() const {
        return count == 0;
    }

    void list::push_front(int data) {
        node* new_node = new node(data, head);
        head = new_node;
        if (!tail) {
            tail = head;
        }
        ++count;
    }

    void list::push_back(int data) {
        node* new_node = new node(data, nullptr);
        if (tail) {
            tail->next = new_node;
            tail = new_node;
        } else {
            head = tail = new_node;
        }
        ++count;
    }

    int list::front() const {
        if (!head) {
            throw std::out_of_range("front() called on empty list");
        }
        return head->data;
    }

    int list::back() const {
        if (!tail) {
            throw std::out_of_range("back() called on empty list");
        }
        return tail->data;
    }

    void list::pop_front() {
        if (!head) {
            throw std::out_of_range("pop_front() called on empty list");
        }
        node* temp = head;
        head = head->next;
        delete temp;
        --count;
        if (!head) {
            tail = nullptr;
        }
    }

    void list::pop_back() {
        if (!tail) {
            throw std::out_of_range("pop_back() called on empty list");
        }
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            count = 0;
            return;
        }

        node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
        --count;
    }
}  // namespace linked_list