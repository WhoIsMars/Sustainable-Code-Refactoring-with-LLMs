#include "binary_search.h"

#include <stdexcept>

namespace binary_search {

std::size_t find(const std::vector<int>& data, int num) {
    if (data.empty()) {
        throw std::domain_error("Array empty.");
    }

    int left = 0;
    int right = static_cast<int>(data.size()) - 1;

    while (left <= right) {
        // Prevent potential overflow
        int middle = left + (right - left) / 2;

        if (data[middle] == num) {
            return static_cast<std::size_t>(middle);
        } else if (data[middle] < num) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    throw std::domain_error("Value not found");
}

}  // namespace binary_search