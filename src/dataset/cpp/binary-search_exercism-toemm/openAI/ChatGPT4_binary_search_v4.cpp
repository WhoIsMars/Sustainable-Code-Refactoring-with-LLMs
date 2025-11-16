#include "binary_search.h"
#include <stdexcept>
#include <vector>

namespace binary_search {

std::size_t find(const std::vector<int>& data, int num) {
    if (data.empty()) throw std::domain_error("Array empty.");
    return find_better(data, num);
}

std::size_t find_better(const std::vector<int>& data, int num) {
    std::size_t left = 0, right = data.size();

    while (left < right) {
        std::size_t middle = left + (right - left) / 2;
        if (data[middle] == num) return middle;
        if (data[middle] < num) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    throw std::domain_error("Value not included.");
}

}  // namespace binary_search