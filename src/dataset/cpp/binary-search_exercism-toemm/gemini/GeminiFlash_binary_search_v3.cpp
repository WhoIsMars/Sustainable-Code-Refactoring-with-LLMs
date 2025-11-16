#include "binary_search.h"

#include <stdexcept>
#include <cmath>

namespace binary_search {

std::size_t find(const std::vector<int>& data, int num) {
    return find_better(data, num);
}

std::size_t find_better(const std::vector<int>& data, int num) {
    if (data.empty()) {
        throw std::domain_error("Value not found");
    }

    std::size_t left = 0;
    std::size_t right = data.size();

    while (left < right) {
        std::size_t middle = left + (right - left) / 2;

        if (data[middle] == num) {
            return middle;
        } else if (data[middle] < num) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    throw std::domain_error("Value not found");
}

}  // namespace binary_search