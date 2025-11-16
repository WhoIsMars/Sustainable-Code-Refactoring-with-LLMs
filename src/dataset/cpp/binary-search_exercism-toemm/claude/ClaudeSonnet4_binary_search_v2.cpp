#include "binary_search.h"

#include <stdexcept>

namespace binary_search {

std::size_t find(const std::vector<int>& data, int num) {
    if (data.empty()) {
        throw std::domain_error("invalid");
    }
    
    std::size_t left = 0;
    std::size_t right = data.size() - 1;

    while (left <= right) {
        std::size_t middle = left + ((right - left) >> 1);
        
        if (data[middle] == num) {
            return middle;
        }
        
        if (num < data[middle]) {
            if (middle == 0) break;
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    throw std::domain_error("invalid");
}

std::size_t find_better(const std::vector<int>& data, int num) {
    return find(data, num);
}

}  // namespace binary_search