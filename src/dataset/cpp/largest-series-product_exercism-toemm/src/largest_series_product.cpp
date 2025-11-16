#include "largest_series_product.h"

#include <stdexcept>
#include <algorithm>

namespace largest_series_product {

int largest_product(const std::string& number, int span) {

    auto length = number.size();

    int biggest_series{};

    if (span > static_cast<int>(length) || length == 0 || span < 0) throw std::domain_error("invalid");

    if (std::any_of(number.begin(), number.end(), 
                                                [] (auto ch) {
                                                    return !isdigit(ch);
                                                })) 
                throw std::domain_error("invalid num");

    for (std::size_t i{}; i < length - span + 1; i++) {

        int product = 1;

        for (int j{}; j < span; j++) {
            int num = number.at(i+j) - '0';
            product *= num;
        }
        

        if (product > biggest_series) biggest_series = product;
    }

    return biggest_series;

}




}  // namespace largest_series_product