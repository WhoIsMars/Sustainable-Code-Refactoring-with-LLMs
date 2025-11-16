#include "largest_series_product.h"

#include <stdexcept>
#include <algorithm>

namespace largest_series_product {

int largest_product(const std::string& number, int span) {
    const auto length = number.size();
    
    if (span > static_cast<int>(length) || length == 0 || span < 0) {
        throw std::domain_error("invalid");
    }
    
    if (span == 0) return 1;
    
    for (char ch : number) {
        if (ch < '0' || ch > '9') {
            throw std::domain_error("invalid num");
        }
    }
    
    int biggest_series = 0;
    int current_product = 1;
    int zero_count = 0;
    
    for (int i = 0; i < span; ++i) {
        int digit = number[i] - '0';
        if (digit == 0) {
            ++zero_count;
        }
        current_product *= digit;
    }
    
    if (zero_count == 0) {
        biggest_series = current_product;
    }
    
    for (std::size_t i = span; i < length; ++i) {
        int old_digit = number[i - span] - '0';
        int new_digit = number[i] - '0';
        
        if (old_digit == 0) {
            --zero_count;
        }
        if (new_digit == 0) {
            ++zero_count;
        }
        
        if (zero_count == 0) {
            current_product = (current_product / old_digit) * new_digit;
            if (current_product > biggest_series) {
                biggest_series = current_product;
            }
        } else if (old_digit == 0 && zero_count == 0) {
            current_product = 1;
            for (int j = 0; j < span; ++j) {
                current_product *= (number[i - span + 1 + j] - '0');
            }
            if (current_product > biggest_series) {
                biggest_series = current_product;
            }
        }
    }
    
    return biggest_series;
}

}  // namespace largest_series_product