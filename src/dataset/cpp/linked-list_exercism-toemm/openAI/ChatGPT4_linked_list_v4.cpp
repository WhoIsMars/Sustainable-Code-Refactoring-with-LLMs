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

    void prepend(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        ++size;
    }

    bool remove(int value) {
        if (!head) return false;

        Node* current = head;
        Node* previous = nullptr;

        while (current) {
            if (current->data == value) {
                if (previous) {
                    previous->next = current->next;
                } else {
                    head = current->next;
                }
                if (current == tail) {
                    tail = previous;
                }
                delete current;
                --size;
                return true;
            }
            previous = current;
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

    size_t getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void traverse(void (*callback)(int)) const {
        Node* current = head;
        while (current) {
            callback(current->data);
            current = current->next;
        }
    }
};

}  // namespace linked_list