#include "largest_series_product.h"

#include <stdexcept>
#include <algorithm>
#include <cctype>

namespace largest_series_product {

int largest_product(const std::string& number, int span) {
    if (span < 0 || span > static_cast<int>(number.size()) || 
        std::any_of(number.begin(), number.end(), [](char ch) { return !std::isdigit(ch); })) {
        throw std::domain_error("invalid");
    }

    if (span == 0) return 1;

    int biggest_series = 0;
    int product = 1;
    int zero_count = 0;

    for (int i = 0; i < static_cast<int>(number.size()); ++i) {
        int digit = number[i] - '0';

        if (digit == 0) {
            ++zero_count;
        } else {
            product *= digit;
        }

        if (i >= span) {
            int prev_digit = number[i - span] - '0';
            if (prev_digit == 0) {
                --zero_count;
            } else {
                product /= prev_digit;
            }
        }

        if (zero_count == 0 && i >= span - 1) {
            biggest_series = std::max(biggest_series, product);
        }
    }

    return biggest_series;
}

}  // namespace largest_series_product