#include "binary.h"

#include <cmath>

namespace binary {

int convert(std::string binary_string) {

    int sum{};

    for (std::size_t i = 0; i < binary_string.size(); i++) {

        char ch = binary_string[binary_string.size() - 1 - i];

        int nr = ch - '0';

        // abort if anyting is non digit
        if (nr < 0 || nr > 9) return 0;


        sum += (nr * pow(2, i));

    }


    return sum;


}


}  // namespace binary
