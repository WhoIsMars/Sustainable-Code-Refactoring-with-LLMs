#include "luhn.h"
#include <string>
#include <algorithm>

using std::string;

bool luhn::valid(string str) {
    int sum = 0;
    bool alternate = false;

    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    if (str.length() <= 1 || !std::all_of(str.begin(), str.end(), ::isdigit))
        return false;

    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        int digit = *it - '0';
        if (alternate) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }
        sum += digit;
        alternate = !alternate;
    }

    return sum % 10 == 0;
}