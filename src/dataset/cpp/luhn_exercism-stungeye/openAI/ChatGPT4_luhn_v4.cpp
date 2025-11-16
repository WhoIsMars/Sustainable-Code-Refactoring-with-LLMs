#include "luhn.h"
#include <string_view>
#include <cctype>

namespace luhn {
    constexpr int convert[] = { 0, 2, 4, 6, 8, 1, 3, 5, 7, 9 };

    bool valid(std::string_view number) {
        int sum = 0, count = 0;

        for (auto it = number.rbegin(); it != number.rend(); ++it) {
            if (*it == ' ') continue;
            if (!std::isdigit(*it)) return false;

            int digit = *it - '0';
            sum += (++count % 2 == 0) ? convert[digit] : digit;
        }

        return count > 1 && sum % 10 == 0;
    }
} // namespace luhn