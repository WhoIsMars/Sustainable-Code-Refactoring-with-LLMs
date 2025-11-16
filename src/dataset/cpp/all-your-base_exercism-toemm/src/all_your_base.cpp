#include "all_your_base.h"

#include <cmath>
#include <stdexcept>

namespace all_your_base {


int to_decimal(unsigned int from_base, const std::vector<unsigned int>& input) {

    int decimal_sum{};

    for (std::size_t i{}; i < input.size(); i++) {

        unsigned int digit = input[input.size() - 1 - i];

        if (digit >= from_base) throw std::invalid_argument("invalid digit");

        decimal_sum += (digit * pow(from_base, i));

    }

    return decimal_sum;

}


std::vector<unsigned int> convert(unsigned int from_base, const std::vector<unsigned int>& input, unsigned int to_base) {

    std::vector<unsigned int> out;
    
    if (from_base < 2 || to_base < 2) throw std::invalid_argument("invalid bases");


    // convert to decimal first
    auto dec_num = to_decimal(from_base, input);


    // convert to another base
    while (dec_num > 0) {


        unsigned int digit = dec_num % to_base;

        out.emplace(out.begin(), digit);

        dec_num /= to_base;

    }



    return out;
}

}  // namespace all_your_base
