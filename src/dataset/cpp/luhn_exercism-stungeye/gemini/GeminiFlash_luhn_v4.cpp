#include "luhn.h"
#include <string_view>

namespace luhn {

bool valid(std::string_view number) {
    int sum = 0;
    int len = 0;
    bool alt = false;

    for (auto it = number.rbegin(); it != number.rend(); ++it) {
        if (*it == ' ') continue;

        if (*it < '0' || *it > '9') return false;

        int n = *it - '0';
        
        if (alt) {
            n *= 2;
            if (n > 9) n -= 9;
        }

        sum += n;
        len++;
        alt = !alt;
    }

    return (len > 1) && (sum % 10 == 0);
}

} // namespace luhn