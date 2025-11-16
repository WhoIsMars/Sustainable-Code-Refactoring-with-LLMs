#include "binary_search.h"

#include <stdexcept>

namespace binary_search {

std::size_t find(const std::vector<int>& data, int num) {
    int left = 0;
    int right = data.size() - 1;

    while (left <= right) {
        size_t middle = left + (right - left) / 2;
        int middle_value = data[middle];

        if (middle_value == num) {
            return middle;
        } else if (num < middle_value) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    throw std::domain_error("Value not found");
}

}  // namespace binary_search