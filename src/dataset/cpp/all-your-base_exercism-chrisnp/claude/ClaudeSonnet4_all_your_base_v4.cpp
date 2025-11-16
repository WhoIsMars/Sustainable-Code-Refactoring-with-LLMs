#include "all_your_base.h"
#include <algorithm>
#include <stdexcept>

all_your_base::digits_t 
all_your_base::convert(all_your_base::uint in_base, 
                       const digits_t &in_representation, 
                       all_your_base::uint out_base)
{
    if (in_base < 2 || out_base < 2) 
        throw std::invalid_argument("bases must be at least 2");
    if (in_representation.empty()) 
        return {};
    
    uint sum = 0;
    uint multiplier = 1;
    
    for (auto digit = in_representation.rbegin();
         digit != in_representation.rend(); 
         ++digit) 
    {
        if (*digit >= in_base) 
            throw std::invalid_argument("invalid digit in input");
        sum += *digit * multiplier;
        multiplier *= in_base;
    }
    
    if (sum == 0) 
        return {0};
    
    digits_t out_representation;
    out_representation.reserve(32);
    
    while (sum > 0) {
        out_representation.push_back(sum % out_base);
        sum /= out_base;
    }
    
    std::reverse(out_representation.begin(), out_representation.end());
    return out_representation;
}