#include "hexadecimal.h"

#include <cctype>

namespace hexadecimal {

int convert(std::string hex_string) {
    int sum = 0;

    for (char ch : hex_string) {
        int num = 0;

        if (ch >= '0' && ch <= '9') {
            num = ch - '0';
        } else if (ch >= 'a' && ch <= 'f') {
            num = 10 + ch - 'a';
        } else {
            return 0; // invalid character
        }

        sum = (sum << 4) + num; // Multiply by 16 using bit-shift and add num
    }

    return sum;
}

}  // namespace hexadecimal