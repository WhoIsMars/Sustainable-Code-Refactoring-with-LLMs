#include "simple_linked_list.h"

#include <stdexcept>

namespace simple_linked_list {

std::size_t List::size() const {
    return current_size;
}

void List::push(int entry) {
    auto new_head = new Element{entry, this->head};
    this->head = new_head;
    ++this->current_size;
}

int List::pop() {
    if (current_size == 0) {
        throw std::domain_error("no elements");
    }

    auto old_head = this->head;
    int data = old_head->data;
    this->head = old_head->next;
    delete old_head;
    --this->current_size;
    return data;
}

void List::reverse() {
    Element* prev = nullptr;
    Element* current = this->head;

    while (current) {
        Element* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    this->head = prev;
}

List::~List() {
    while (this->head) {
        auto next = this->head->next;
        delete this->head;
        this->head = next;
    }
}

}  // namespace simple_linked_list