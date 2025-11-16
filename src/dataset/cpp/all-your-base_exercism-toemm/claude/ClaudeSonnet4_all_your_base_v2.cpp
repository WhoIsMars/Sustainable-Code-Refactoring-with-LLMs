#include "all_your_base.h"

#include <stdexcept>

namespace all_your_base {

int to_decimal(unsigned int from_base, const std::vector<unsigned int>& input) {
    int decimal_sum{};
    unsigned int power = 1;

    for (auto it = input.rbegin(); it != input.rend(); ++it) {
        if (*it >= from_base) throw std::invalid_argument("invalid digit");
        decimal_sum += (*it * power);
        power *= from_base;
    }

    return decimal_sum;
}

std::vector<unsigned int> convert(unsigned int from_base, const std::vector<unsigned int>& input, unsigned int to_base) {
    if (from_base < 2 || to_base < 2) throw std::invalid_argument("invalid bases");

    auto dec_num = to_decimal(from_base, input);
    
    if (dec_num == 0) return {0};

    std::vector<unsigned int> out;
    out.reserve(32); // Reserve space to avoid reallocations

    while (dec_num > 0) {
        out.push_back(dec_num % to_base);
        dec_num /= to_base;
    }

    std::reverse(out.begin(), out.end());
    return out;
}

}  // namespace all_your_base