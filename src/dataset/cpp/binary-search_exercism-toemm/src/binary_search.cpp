#include "binary_search.h"

#include <stdexcept>
#include <cmath>

namespace binary_search {

    
std::size_t find(const std::vector<int>& data, int num) {

/* 
    if (data.empty()) throw std::domain_error("Array empty.");

    int container_size = data.size() - 1;
    int new_middle = (container_size / 2.0);

    int old_middle{};
    float delta{};

    while(true) {
    
        delta = std::ceil(std::abs((old_middle - new_middle) / 2.0));
        old_middle = new_middle;

        if (num > data[new_middle]) {
            new_middle += delta; 
        } else if (num < data[new_middle]) {
            new_middle -= delta;
        }

        // value found
        if (num == data[new_middle]) {
            break;
        // value not found but delta == 1, means value isn't included
        } else if (delta == 1.0)
            throw std::domain_error("Value not included.");
  

    }
 */

    return find_better(data, num);
}

std::size_t find_better(const std::vector<int>& data, int num) {

    int left{0};
    int right = data.size() - 1;

    while (left <= right) {
        
        int middle = left + ((right - left) / 2);
        int element = data[middle];

        if (element == num) return middle;

        if (num < element) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    throw std::domain_error("invalid");
}



}  // namespace binary_search
