#include "hexadecimal.h"

#include <cmath>

namespace hexadecimal {

int convert(std::string hex_string) {

    int sum{};

    for (std::size_t i{}; i < hex_string.length(); i++) {

        char ch = hex_string[hex_string.length() - 1 -i];


        int num{};

        // 
        if (ch >= '0' && ch <= '9') {
            num = ch - '0';
        }

        else if (ch >= 'a' && ch <= 'f') {

            // f (102) - 87 = 15
            num = 10 + ch - 'a';
        }

        // invalid
        else return 0;

        sum += (num * std::pow(16, i));



    }

    return sum;


}

}  // namespace hexadecimal
