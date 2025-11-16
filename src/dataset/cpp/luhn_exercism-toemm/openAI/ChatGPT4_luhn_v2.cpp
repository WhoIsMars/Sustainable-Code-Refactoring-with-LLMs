#include "luhn.h"
#include <cctype>

namespace luhn {

bool valid(const std::string& test) {
    int sum = 0;
    bool double_digit = false;
    int digit_count = 0;

    for (auto it = test.rbegin(); it != test.rend(); ++it) {
        if (std::isspace(*it)) continue;

        if (std::isdigit(*it)) {
            int digit = *it - '0';
            if (double_digit) {
                digit *= 2;
                if (digit > 9) digit -= 9;
            }
            sum += digit;
            double_digit = !double_digit;
            ++digit_count;
        } else {
            return false;
        }
    }

    return digit_count > 1 && sum % 10 == 0;
}

}  // namespace luhn