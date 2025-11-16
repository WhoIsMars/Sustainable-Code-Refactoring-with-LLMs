#include "luhn.h"
#include <string>
#include <algorithm>

using std::string;

bool luhn::valid(string str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    if (str.length() <= 1) {
        return false;
    }

    int sum = 0;
    bool double_digit = false;
    for (int i = str.length() - 1; i >= 0; --i) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }

        int digit = str[i] - '0';

        if (double_digit) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }

        sum += digit;
        double_digit = !double_digit;
    }

    return (sum % 10 == 0);
}