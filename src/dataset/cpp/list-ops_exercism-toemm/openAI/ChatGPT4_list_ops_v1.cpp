#include "list_ops.h"

namespace list_ops {

    // Assuming the list_ops namespace is intended to provide operations on lists,
    // here are some optimized implementations for common list operations.

    // Function to calculate the sum of elements in a list
    template <typename T>
    T sum(const std::vector<T>& list) {
        T total = 0;
        for (const auto& item : list) {
            total += item;
        }
        return total;
    }

    // Function to find the maximum element in a list
    template <typename T>
    T max(const std::vector<T>& list) {
        if (list.empty()) {
            throw std::invalid_argument("List is empty");
        }
        return *std::max_element(list.begin(), list.end());
    }

    // Function to reverse a list
    template <typename T>
    void reverse(std::vector<T>& list) {
        std::reverse(list.begin(), list.end());
    }

    // Function to remove duplicates from a list
    template <typename T>
    void remove_duplicates(std::vector<T>& list) {
        std::unordered_set<T> seen;
        auto it = list.begin();
        while (it != list.end()) {
            if (seen.find(*it) != seen.end()) {
                it = list.erase(it);
            } else {
                seen.insert(*it);
                ++it;
            }
        }
    }

    // Function to sort a list
    template <typename T>
    void sort(std::vector<T>& list) {
        std::sort(list.begin(), list.end());
    }

}  // namespace list_ops