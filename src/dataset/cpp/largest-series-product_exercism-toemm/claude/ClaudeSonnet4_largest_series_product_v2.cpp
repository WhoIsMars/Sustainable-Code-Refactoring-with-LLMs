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
    
    // Single pass validation and conversion
    std::vector<int> digits;
    digits.reserve(length);
    
    for (char ch : number) {
        if (ch < '0' || ch > '9') {
            throw std::domain_error("invalid num");
        }
        digits.push_back(ch - '0');
    }
    
    int biggest_series = 0;
    int current_product = 1;
    
    // Calculate initial product
    for (int j = 0; j < span; j++) {
        current_product *= digits[j];
    }
    biggest_series = current_product;
    
    // Sliding window with division/multiplication
    for (std::size_t i = 1; i <= length - span; i++) {
        if (digits[i - 1] == 0) {
            // Recalculate product when encountering zero
            current_product = 1;
            for (int j = 0; j < span; j++) {
                current_product *= digits[i + j];
            }
        } else {
            // Slide window: divide by outgoing, multiply by incoming
            current_product = (current_product / digits[i - 1]) * digits[i + span - 1];
        }
        
        if (current_product > biggest_series) {
            biggest_series = current_product;
        }
    }
    
    return biggest_series;
}

}  // namespace largest_series_product