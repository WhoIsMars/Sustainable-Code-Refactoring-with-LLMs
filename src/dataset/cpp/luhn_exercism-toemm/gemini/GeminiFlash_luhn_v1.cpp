#include "luhn.h"
#include <algorithm>
#include <cctype>

namespace luhn {

bool valid(std::string test) {
    int sum = 0;
    int length = 0;
    bool alt = false;

    for (auto it = test.rbegin(); it != test.rend(); ++it) {
        if (std::isspace(*it)) continue;

        if (!std::isdigit(*it)) return false;

        int digit = *it - '0';
        
        if (alt) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }

        sum += digit;
        length++;
        alt = !alt;
    }

    return (length > 1) && (sum % 10 == 0);
}

}  // namespace luhn