#include "luhn.h"
#include <cctype>

namespace luhn {

bool valid(const std::string& test) {
    int sum = 0;
    int ctr = 0;

    for (auto it = test.rbegin(); it != test.rend(); ++it) {
        if (std::isspace(*it)) continue;
        if (!std::isdigit(*it)) return false;

        int nr = *it - '0';
        if (ctr++ % 2 == 1) {
            nr = (nr * 2 > 9) ? nr * 2 - 9 : nr * 2;
        }
        sum += nr;
    }

    return ctr > 1 && sum % 10 == 0;
}

}  // namespace luhn