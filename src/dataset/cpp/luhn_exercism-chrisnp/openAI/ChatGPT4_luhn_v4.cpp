#include "luhn.h"
#include <cctype>

bool luhn::valid(std::string num) {
    int csum = 0, len = 0;
    for (auto it = num.rbegin(); it != num.rend(); ++it) {
        if (*it == ' ') continue;
        if (!std::isdigit(*it)) return false;
        int d = *it - '0';
        if (len++ % 2 != 0) d = (d > 4) ? (d * 2 - 9) : (d * 2);
        csum += d;
    }
    return len > 1 && csum % 10 == 0;
}