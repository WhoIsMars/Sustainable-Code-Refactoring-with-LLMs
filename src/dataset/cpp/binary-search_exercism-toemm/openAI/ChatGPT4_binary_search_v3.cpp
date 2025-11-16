#include "binary_search.h"

#include <stdexcept>
#include <vector>

namespace binary_search {

std::size_t find(const std::vector<int>& data, int num) {
    return find_better(data, num);
}

std::size_t find_better(const std::vector<int>& data, int num) {
    if (data.empty()) throw std::domain_error("Array empty.");

    int left = 0, right = static_cast<int>(data.size()) - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (data[middle] == num) return middle;

        if (num < data[middle]) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    throw std::domain_error("Value not included.");
}

}  // namespace binary_search