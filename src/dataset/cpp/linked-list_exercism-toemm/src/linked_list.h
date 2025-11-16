#pragma once

#include <stdexcept>

namespace linked_list {

template<typename T>
class List {

    struct Element {
        public:
            Element(const T& data, Element* prev_ptr) : _data(data), next(nullptr), prev(prev_ptr) {}
            Element* get_next() const { return next; }
            Element* get_prev() const { return prev; }

            void set_prev(Element* prev_ptr) { prev = prev_ptr; }
            void set_next(Element* next_ptr) { next = next_ptr; }
            T get_data() const { return _data; }

        private:
            T _data;
            Element* next;
            Element* prev;
    };

    public:
        List() : head(nullptr), tail(nullptr) {}

        void push(const T& data) {

            // first elem
            if (head == nullptr) {
                head = new Element{data, nullptr};
                tail = head;
            }

            else {
                tail->set_next(new Element(data, tail));
                tail = tail->get_next();
            }
        }

        T pop() {

            T data{};

            data = tail->get_data();

            if (head != tail) {

                tail->get_prev()->set_next(nullptr);
                tail = tail->get_prev();
                

            } else {
                head = nullptr;
                tail = head;

            }

            return data;

        }

        T shift() {

            if (head != nullptr) {

                T temp = head->get_data();

                // change prev ptr of next next node
                if (head->get_next() != nullptr) {
                    head->get_next()->set_prev(nullptr);
                    this->head = head->get_next();

                } else {
                    delete head;
                    this->head = nullptr;
                }
                
                return temp;

            } else throw std::domain_error("no element in list to shift");

        }
        void unshift(const T& data) {

            Element* new_elem = new Element{data, nullptr};

            if (head != nullptr) {

                // if there is a followup node
                new_elem->set_next(head);
                head->set_prev(new_elem);
            } 

            // finally add new elem to start
            this->head = new_elem;

        }

        int count() const {

            int ctr{};
            auto curr = this->head;

            while(curr != nullptr) {
                curr = curr->get_next();
                ctr++;
            }

            return ctr;
        }

        bool erase(const T& erase_data) {

            Element* current = head;

            while (current != nullptr) {

                if (current->get_data() == erase_data) {

                    // check if forward node
                    if (current->get_next() != nullptr) {

                        // check for first element
                        if (current->get_prev() != nullptr) {

                            current->get_next()->set_prev(current->get_prev());
                            current->get_prev()->set_next(current->get_next());

                        // the head node
                        } else {

                            this->head = current->get_next();
                            current->get_next()->set_prev(nullptr);

                        }

                    // the last node (tail)
                    } else {

                        if (current->get_prev() != nullptr) {
                            current->get_prev()->set_next(nullptr);
                            tail = current->get_prev();

                        // only 1 node and it's a hit
                        } else {
                            this->head = nullptr;

                        }

                    }

                    delete current;

                    return true;

                }

                current = current->get_next();

            }

            return false;


        }

    private:
        Element* head;
        Element* tail;



};
    
}  // namespace linked_list
