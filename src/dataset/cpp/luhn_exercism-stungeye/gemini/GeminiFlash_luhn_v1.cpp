#include "luhn.h"
#include <string_view>

namespace luhn {

bool valid(std::string_view number) {
    int sum = 0;
    int len = 0;
    int n;
    bool alt = false;

    // Iterate backwards through the string.
    for (auto it = number.rbegin(); it != number.rend(); ++it) {
        if (*it >= '0' && *it <= '9') {
            n = *it - '0';
            if (alt) {
                n *= 2;
                if (n > 9) {
                    n -= 9;
                }
            }
            sum += n;
            alt = !alt;
            len++;
        } else if (*it != ' ') {
            return false; // Invalid character
        }
    }

    return (len > 1) && (sum % 10 == 0);
}

} // namespace luhn