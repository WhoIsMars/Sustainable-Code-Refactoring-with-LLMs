#include "all_your_base.h"
#include <algorithm>
#include <stdexcept>

all_your_base::digits_t 
all_your_base::convert(all_your_base::uint in_base, 
                       const digits_t &in_representation, 
                       all_your_base::uint out_base)
{
    all_your_base::digits_t out_representation {};
    if (in_base < 2 || out_base < 2) 
        throw std::invalid_argument("bases must be at least 2");
    if (in_representation.empty()) 
        return out_representation;

    // Calculate the decimal value directly
    int sum = 0;
    for (const auto &digit : in_representation) {
        if (digit >= in_base) 
            throw std::invalid_argument("invalid digit in input");
        sum = sum * in_base + digit;
    }

    // Convert to the output base
    do {
        out_representation.push_back(sum % out_base);
        sum /= out_base;
    } while (sum > 0);

    std::reverse(out_representation.begin(), out_representation.end());
    return out_representation;
}