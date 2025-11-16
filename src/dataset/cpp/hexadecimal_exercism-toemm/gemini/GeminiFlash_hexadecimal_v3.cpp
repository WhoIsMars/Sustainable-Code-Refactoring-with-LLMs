#include "hexadecimal.h"

#include <algorithm>
#include <cctype>

namespace hexadecimal {

int convert(std::string hex_string) {
    int sum = 0;
    int power_of_16 = 1;

    for (auto it = hex_string.rbegin(); it != hex_string.rend(); ++it) {
        char ch = *it;
        int num;

        if (std::isdigit(ch)) {
            num = ch - '0';
        } else if (ch >= 'a' && ch <= 'f') {
            num = 10 + ch - 'a';
        } else if (ch >= 'A' && ch <= 'F') {
            num = 10 + ch - 'A';
        }
        else {
            return 0;
        }

        sum += num * power_of_16;
        power_of_16 *= 16;
    }

    return sum;
}

}  // namespace hexadecimal