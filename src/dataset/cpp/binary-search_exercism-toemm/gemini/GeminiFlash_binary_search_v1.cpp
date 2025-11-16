#include "binary_search.h"

#include <stdexcept>
#include <cmath>

namespace binary_search {

std::size_t find(const std::vector<int>& data, int num) {
    if (data.empty()) {
        throw std::domain_error("Array empty.");
    }

    int left = 0;
    int right = data.size() - 1;

    while (left <= right) {
        size_t middle = left + (right - left) / 2; // Prevent potential overflow
        int element = data[middle];

        if (element == num) {
            return middle;
        } else if (num < element) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    throw std::domain_error("Value not found.");
}

std::size_t find_better(const std::vector<int>& data, int num) {
    return find(data, num);
}

}  // namespace binary_search