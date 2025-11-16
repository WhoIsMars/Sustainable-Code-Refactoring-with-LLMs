#include "largest_series_product.h"

#include <stdexcept>
#include <algorithm>
#include <numeric>

namespace largest_series_product {

int largest_product(const std::string& number, int span) {
    auto length = number.size();

    if (span > static_cast<int>(length) || length == 0 || span < 0) {
        throw std::domain_error("invalid");
    }

    if (std::any_of(number.begin(), number.end(), [](auto ch) { return !isdigit(ch); })) {
        throw std::domain_error("invalid num");
    }

    if (span == 0) return 1;

    int biggest_series = 0;

    for (std::size_t i = 0; i <= length - span; ++i) {
        int product = 1;
        for (int j = 0; j < span; ++j) {
            product *= (number[i + j] - '0');
        }
        biggest_series = std::max(biggest_series, product);
    }

    return biggest_series;
}

}  // namespace largest_series_product