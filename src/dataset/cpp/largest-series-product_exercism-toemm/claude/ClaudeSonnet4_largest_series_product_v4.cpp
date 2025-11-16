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
    int product = 1;
    
    for (int i = 0; i < span; ++i) {
        product *= (number[i] - '0');
    }
    biggest_series = product;
    
    for (std::size_t i = span; i < length; ++i) {
        const int old_digit = number[i - span] - '0';
        const int new_digit = number[i] - '0';
        
        if (old_digit == 0) {
            product = 1;
            for (int j = i - span + 1; j <= static_cast<int>(i); ++j) {
                product *= (number[j] - '0');
            }
        } else {
            product = (product / old_digit) * new_digit;
        }
        
        if (product > biggest_series) {
            biggest_series = product;
        }
    }
    
    return biggest_series;
}

}  // namespace largest_series_product