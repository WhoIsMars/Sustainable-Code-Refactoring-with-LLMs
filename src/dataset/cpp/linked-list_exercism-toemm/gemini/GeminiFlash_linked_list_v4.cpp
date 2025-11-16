#include "linked_list.h"
#include <stdexcept>

namespace linked_list {

list::list() : head(nullptr) {}

list::~list() {
  node* current = head;
  while (current != nullptr) {
    node* next = current->next;
    delete current;
    current = next;
  }
}

void list::push_front(int data) {
  node* new_node = new node(data);
  new_node->next = head;
  head = new_node;
}

int list::pop_front() {
  if (head == nullptr) {
    throw std::runtime_error("Cannot pop from empty list");
  }
  int data = head->data;
  node* temp = head;
  head = head->next;
  delete temp;
  return data;
}
}  // namespace linked_list