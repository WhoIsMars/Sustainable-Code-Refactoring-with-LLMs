#include "simple_linked_list.h"

#include <stdexcept>

namespace simple_linked_list {

std::size_t List::size() const {
    return current_size;
}

void List::push(int entry) {
    // TODO: Implement a function that pushes an Element with `entry` as data to
    // the front of the list.
    this->current_size++;

    auto old_head = this->head;

    this->head = new Element{entry};

    this->head->next = old_head;
    

}

int List::pop() {
    // TODO: Implement a function that returns the data value of the first
    // element in the list then discard that element.
    if (current_size >= 1) {

        auto old_head = this->head;
        auto data = old_head->data;
        this->head = old_head->next;
        delete old_head;
        current_size--;
        return data;

    } else throw std::domain_error("no elements");
}

void List::reverse() {
    // TODO: Implement a function to reverse the order of the elements in the
    // list.

    if (current_size >= 1)  {

        Element* before = nullptr;
        Element* current = head;
        Element* after = head->next;

        while (current != nullptr) {

            after = current->next;

            current->next = before;

            before = current;

            current = after;

        }

        this->head = before;

    }
    

}

List::~List() {
    // TODO: Ensure that all resources are freed on destruction

    for (Element* e = this->head; e != nullptr; ) {
        Element* next = e->next;
        delete e;
        e = nullptr;
        e = next;
    }
}

}  // namespace simple_linked_list
