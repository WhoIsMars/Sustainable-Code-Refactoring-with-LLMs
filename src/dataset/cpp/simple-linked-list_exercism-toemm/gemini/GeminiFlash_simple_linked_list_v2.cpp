#include "simple_linked_list.h"

#include <stdexcept>
#include <algorithm> // For std::swap

namespace simple_linked_list {

std::size_t List::size() const {
    return current_size;
}

void List::push(int entry) {
    Element* new_head = new Element{entry, head};
    head = new_head;
    current_size++;
}

int List::pop() {
    if (head == nullptr) {
        throw std::domain_error("no elements");
    }

    Element* old_head = head;
    int data = old_head->data;
    head = old_head->next;
    delete old_head;
    current_size--;
    return data;
}

void List::reverse() {
    if (current_size <= 1) return;

    Element* prev = nullptr;
    Element* current = head;
    Element* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head = prev;
}


List::~List() {
    Element* current = head;
    while (current != nullptr) {
        Element* next = current->next;
        delete current;
        current = next;
    }
}

}  // namespace simple_linked_list