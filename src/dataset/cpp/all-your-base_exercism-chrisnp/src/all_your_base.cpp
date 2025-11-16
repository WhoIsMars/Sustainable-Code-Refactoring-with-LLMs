#include "all_your_base.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>

all_your_base::digits_t 
all_your_base::convert(all_your_base::uint in_base, 
                       const digits_t &in_representation, 
                       all_your_base::uint out_base)
{
    all_your_base::digits_t out_representation {};
    if (in_base < 2 || out_base < 2) 
        throw std::invalid_argument("bases must be at least 2");
    if (in_representation.size() == 0) 
        return out_representation;
    int sum { 0 }, position { 0 };
    for (auto digit = in_representation.rbegin();
              digit != in_representation.rend(); 
              ++digit) 
    {
        if (*digit >= in_base) 
            throw std::invalid_argument("invalid digit in input");
        sum += *digit * pow(in_base, position);
        ++position;
    }
    while (sum >= 1) {
        out_representation.push_back(sum % out_base);
        sum /= out_base;
    } 
    reverse(begin(out_representation), end(out_representation));
    return out_representation;
}
