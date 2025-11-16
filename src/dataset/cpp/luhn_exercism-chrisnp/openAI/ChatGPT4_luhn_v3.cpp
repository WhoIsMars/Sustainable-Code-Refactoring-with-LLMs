#include "luhn.h"
#include <cctype>

bool luhn::valid(std::string num) {
    int csum = 0;
    bool alternate = false;

    for (auto it = num.rbegin(); it != num.rend(); ++it) {
        if (*it == ' ') continue;
        if (!std::isdigit(*it)) return false;

        int d = *it - '0';
        if (alternate) {
            d *= 2;
            if (d > 9) d -= 9;
        }
        csum += d;
        alternate = !alternate;
    }

    return csum > 0 && csum % 10 == 0;
}