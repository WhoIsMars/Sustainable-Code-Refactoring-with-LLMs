#include "luhn.h"
#include <algorithm>
#include <cctype>

using namespace std;

bool luhn::valid(string num) {
    size_t len = num.length();
    if (len < 2) return false;

    int sum = 0;
    int digit;
    bool alt = false;

    for (int i = len - 1; i >= 0; --i) {
        if (num[i] == ' ') continue;

        if (!isdigit(num[i])) return false;

        digit = num[i] - '0';

        if (alt) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }

        sum += digit;
        alt = !alt;
    }

    return (sum % 10 == 0) && (len - count(num.begin(), num.end(), ' ') >= 2);
}