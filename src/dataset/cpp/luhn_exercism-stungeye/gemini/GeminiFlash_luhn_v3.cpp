#include "luhn.h"
#include <numeric>

namespace luhn {
    bool valid(std::string_view number) {
        int sum = 0;
        int len = 0;
        bool alt = false;

        for (auto it = number.rbegin(); it != number.rend(); ++it) {
            if (*it == ' ') continue;

            if (!isdigit(*it)) return false;

            int n = *it - '0';
            if (n < 0 || n > 9) return false;

            if (alt) {
                n *= 2;
                if (n > 9) n -= 9;
            }

            sum += n;
            alt = !alt;
            len++;
        }

        return (len > 1) && (sum % 10 == 0);
    }
} // namespace luhn