#include "linked_list.h"

namespace linked_list {

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;
    size_t size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }

    void append(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    void remove(int value) {
        if (!head) return;

        Node* current = head;
        Node* prev = nullptr;

        while (current) {
            if (current->data == value) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                if (current == tail) {
                    tail = prev;
                }
                delete current;
                --size;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    bool find(int value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
        size = 0;
    }

    size_t get_size() const {
        return size;
    }
};

}  // namespace linked_list