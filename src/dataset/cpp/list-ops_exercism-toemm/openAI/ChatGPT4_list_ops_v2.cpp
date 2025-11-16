#include "list_ops.h"
#include <algorithm>
#include <list>

namespace list_ops {

    // Optimized function to remove duplicates from a list
    template <typename T>
    void remove_duplicates(std::list<T>& lst) {
        lst.sort(); // Sort the list to bring duplicates together
        lst.unique(); // Remove consecutive duplicates
    }

    // Optimized function to merge two sorted lists into one sorted list
    template <typename T>
    std::list<T> merge_sorted_lists(const std::list<T>& lst1, const std::list<T>& lst2) {
        std::list<T> result;
        std::merge(lst1.begin(), lst1.end(), lst2.begin(), lst2.end(), std::back_inserter(result));
        return result;
    }

    // Optimized function to reverse a list
    template <typename T>
    void reverse_list(std::list<T>& lst) {
        lst.reverse(); // In-place reverse for efficiency
    }

}  // namespace list_ops