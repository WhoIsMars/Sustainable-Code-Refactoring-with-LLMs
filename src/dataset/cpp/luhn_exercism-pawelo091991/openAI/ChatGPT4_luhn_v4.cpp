#include "luhn.h"
#include <string>
#include <algorithm>

using std::string;

bool luhn::valid(const string& str) {
    int sum = 0;
    bool alternate = false;

    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        if (*it == ' ') continue;
        if (*it < '0' || *it > '9') return false;

        int digit = *it - '0';
        if (alternate) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }
        sum += digit;
        alternate = !alternate;
    }

    return sum > 0 && sum % 10 == 0;
}