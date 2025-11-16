#include "simple_linked_list.h"

#include <stdexcept>

namespace simple_linked_list {

std::size_t List::size() const {
    return current_size;
}

void List::push(int entry) {
    Element* new_element = new Element{entry, this->head};
    this->head = new_element;
    ++this->current_size;
}

int List::pop() {
    if (current_size == 0) {
        throw std::domain_error("no elements");
    }
    
    Element* old_head = this->head;
    int data = old_head->data;
    this->head = old_head->next;
    delete old_head;
    --current_size;
    return data;
}

void List::reverse() {
    if (current_size <= 1) {
        return;
    }

    Element* prev = nullptr;
    Element* current = head;

    while (current != nullptr) {
        Element* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    this->head = prev;
}

List::~List() {
    Element* current = this->head;
    while (current != nullptr) {
        Element* next = current->next;
        delete current;
        current = next;
    }
}

}  // namespace simple_linked_list