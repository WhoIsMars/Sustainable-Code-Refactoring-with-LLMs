#if !defined(BINARY_SEARCH_TREE_H)
#define BINARY_SEARCH_TREE_H

#include <memory>
#include <vector>
#include <iterator>
#include <cstddef>

namespace binary_search_tree {

using namespace std;

template <typename T>
class binary_tree{

    public:

    binary_tree(const T& data) : _data(data), _left(nullptr), _right(nullptr), _parent(nullptr) {}
    
    const unique_ptr<binary_tree<T>>& left() const { return _left; }
    const unique_ptr<binary_tree<T>>& right() const { return _right; }
    binary_tree<T>* parent() const { return _parent; }
    const T& data() const { return _data; }
    void insert(const T& data) {

        if (data <= _data) {
    
            if (_left != nullptr) _left->insert(data);
            else {
                _left = make_unique<binary_tree<T>>(data);
                _left->_parent = this;
            }
    
        } else {
    
            if (_right != nullptr) _right->insert(data);
            else {
                _right = make_unique<binary_tree<T>>(data);
                _right->_parent = this;
            }
    
        }
    }

    // Iterator
    struct Iterator {

        using reference = const T&;
        using pointer = const T*;

        Iterator(binary_tree<T>* ptr) : m_ptr(ptr) {}

        reference operator*() const { return m_ptr->data(); }

        // increment operator sorting
        Iterator& operator++() {

            if (m_ptr == nullptr) return *this;

            binary_tree<T>* current = m_ptr;

            // we have a right subtree
            if (m_ptr->right() != nullptr) {

                // if we have a right tree, the next element is the left most in the right subtree
                m_ptr = m_ptr->right().get();
                while (m_ptr->left()) {
                    m_ptr = m_ptr->left().get();
                }


            // we don't have a right subtree, move up
            } else {

                // if there is a parent and we come from the right, move up
                m_ptr = m_ptr->parent();
                while(m_ptr != nullptr && m_ptr->right().get() == current) {
                    current = m_ptr;
                    m_ptr = m_ptr->parent();
                }
            }
            return *this;
        }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!= (const Iterator& a, const Iterator& b) { return !(a == b); }

        private:
        binary_tree<T>* m_ptr;

    };

    //Iterator
    Iterator begin() {
        binary_tree<T>* current = this;
    
        while (current->left()) {
            current = current->left().get();
        }
    
        return Iterator(current);
    
    }
    
    Iterator end() {
        return Iterator(nullptr);
    }


    private:
    const T _data;
    unique_ptr<binary_tree<T>> _left;
    unique_ptr<binary_tree<T>> _right;
    binary_tree<T>* _parent;
    

};








    
}  // namespace binary_search_tree




#endif  // BINARY_SEARCH_TREE_H