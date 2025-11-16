#include "luhn.h"
#include <string>
#include <algorithm>
#include <numeric>

using std::string;

bool luhn::valid(string str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    if (str.length() <= 1) {
        return false;
    }

    if (!std::all_of(str.begin(), str.end(), ::isdigit)) {
        return false;
    }

    int sum = 0;
    for (size_t i = 0; i < str.length(); ++i) {
        int digit = str[str.length() - 1 - i] - '0';

        if ((i + 1) % 2 == 0) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }
        sum += digit;
    }

    return (sum % 10 == 0);
}