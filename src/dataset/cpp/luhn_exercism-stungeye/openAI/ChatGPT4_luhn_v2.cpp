#include "luhn.h"
#include <numeric>
#include <string_view>

namespace luhn {
    constexpr int convert[] = { 0, 2, 4, 6, 8, 1, 3, 5, 7, 9 };

    bool valid(std::string_view number) {
        int sum = 0;
        bool alternate = false;
        int digit_count = 0;

        for (auto it = number.rbegin(); it != number.rend(); ++it) {
            const char c = *it;
            if (c >= '0' && c <= '9') {
                int n = c - '0';
                sum += alternate ? convert[n] : n;
                alternate = !alternate;
                ++digit_count;
            } else if (c != ' ') {
                return false;
            }
        }

        return digit_count > 1 && sum % 10 == 0;
    }
} // namespace luhn