#include "hexadecimal.h"

namespace hexadecimal {

int convert(std::string hex_string) {
    int sum{};
    int power = 1;

    for (int i = hex_string.length() - 1; i >= 0; i--) {
        char ch = hex_string[i];
        int num{};

        if (ch >= '0' && ch <= '9') {
            num = ch - '0';
        }
        else if (ch >= 'a' && ch <= 'f') {
            num = 10 + ch - 'a';
        }
        else return 0;

        sum += num * power;
        power <<= 4;
    }

    return sum;
}

}  // namespace hexadecimal