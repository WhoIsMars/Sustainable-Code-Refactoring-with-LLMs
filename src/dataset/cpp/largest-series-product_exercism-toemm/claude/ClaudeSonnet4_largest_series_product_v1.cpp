#include "largest_series_product.h"

#include <stdexcept>
#include <algorithm>

namespace largest_series_product {

int largest_product(const std::string& number, int span) {
    const auto length = static_cast<int>(number.size());

    if (span > length || length == 0 || span < 0) {
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
    
    // Calculate first window
    int product = 1;
    for (int j = 0; j < span; ++j) {
        product *= digits[j];
    }
    biggest_series = product;

    // Sliding window optimization
    for (int i = 1; i <= length - span; ++i) {
        if (digits[i - 1] == 0) {
            // Recalculate from scratch when removing zero
            product = 1;
            for (int j = 0; j < span; ++j) {
                product *= digits[i + j];
            }
        } else {
            // Slide window: remove first, add last
            product = (product / digits[i - 1]) * digits[i + span - 1];
        }
        
        if (product > biggest_series) {
            biggest_series = product;
        }
    }

    return biggest_series;
}

}  // namespace largest_series_product