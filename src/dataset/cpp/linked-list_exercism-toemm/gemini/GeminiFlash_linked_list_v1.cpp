#include "linked_list.h"
#include <stdexcept>

namespace linked_list {

    node::node(int data_) : data{data_}, next{nullptr} {}

    list::list() : head{nullptr} {}

    list::~list() {
        while (head != nullptr) {
            node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void list::push_front(int data) {
        node* new_node = new node(data);
        new_node->next = head;
        head = new_node;
    }

    int list::pop_front() {
        if (head == nullptr) {
            throw std::out_of_range("Cannot pop from an empty list");
        }
        int data = head->data;
        node* temp = head;
        head = head->next;
        delete temp;
        return data;
    }

    void list::push_back(int data) {
        node* new_node = new node(data);
        if (head == nullptr) {
            head = new_node;
            return;
        }
        node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }

    int list::pop_back() {
        if (head == nullptr) {
            throw std::out_of_range("Cannot pop from an empty list");
        }
        if (head->next == nullptr) {
            int data = head->data;
            delete head;
            head = nullptr;
            return data;
        }
        node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        int data = current->next->data;
        delete current->next;
        current->next = nullptr;
        return data;
    }

    int list::front() const {
        if (head == nullptr) {
            throw std::out_of_range("Cannot get front of an empty list");
        }
        return head->data;
    }

    int list::back() const {
        if (head == nullptr) {
            throw std::out_of_range("Cannot get back of an empty list");
        }
        const node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        return current->data;
    }
}  // namespace linked_list