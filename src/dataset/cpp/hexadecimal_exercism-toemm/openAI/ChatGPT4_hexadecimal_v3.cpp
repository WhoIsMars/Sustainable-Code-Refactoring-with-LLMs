#include "hexadecimal.h"

#include <string>

namespace hexadecimal {

int convert(const std::string& hex_string) {
    int sum = 0;

    for (char ch : hex_string) {
        int num = 0;

        if (ch >= '0' && ch <= '9') {
            num = ch - '0';
        } else if (ch >= 'a' && ch <= 'f') {
            num = 10 + ch - 'a';
        } else {
            return 0;
        }

        sum = sum * 16 + num;
    }

    return sum;
}

}  // namespace hexadecimal