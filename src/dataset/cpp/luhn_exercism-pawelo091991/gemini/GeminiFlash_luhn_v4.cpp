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

    int sum = 0;
    bool double_it = false;

    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        if (*it < '0' || *it > '9') {
            return false;
        }

        int digit = *it - '0';

        if (double_it) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }

        sum += digit;
        double_it = !double_it;
    }

    return (sum % 10 == 0);
}