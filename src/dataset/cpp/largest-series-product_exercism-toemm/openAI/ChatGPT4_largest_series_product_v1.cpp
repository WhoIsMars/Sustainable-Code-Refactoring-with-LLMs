#include "largest_series_product.h"

#include <stdexcept>
#include <algorithm>
#include <cctype>

namespace largest_series_product {

int largest_product(const std::string& number, int span) {
    if (span > static_cast<int>(number.size()) || span < 0) 
        throw std::domain_error("invalid");

    if (std::any_of(number.begin(), number.end(), [](char ch) { return !std::isdigit(ch); }))
        throw std::domain_error("invalid num");

    int biggest_series = 0, product = 1, zero_count = 0;

    for (int i = 0; i < static_cast<int>(number.size()); ++i) {
        int num = number[i] - '0';

        if (num == 0) {
            zero_count++;
            product = 1;
        } else {
            product *= num;
        }

        if (i >= span) {
            int prev_num = number[i - span] - '0';
            if (prev_num == 0) {
                zero_count--;
            } else {
                product /= prev_num;
            }
        }

        if (zero_count == 0 && i >= span - 1) {
            biggest_series = std::max(biggest_series, product);
        }
    }

    return biggest_series;
}

}  // namespace largest_series_product