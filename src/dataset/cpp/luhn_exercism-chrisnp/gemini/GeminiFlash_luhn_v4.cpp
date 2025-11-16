#include "luhn.h"
#include <algorithm>
#include <cctype>

using namespace std;

bool luhn::valid(string num) {
    num.erase(remove(num.begin(), num.end(), ' '), num.end());
    size_t len = num.length();
    if (len < 2) return false;

    int csum = 0;
    for (size_t i = 0; i < len; ++i) {
        if (!isdigit(num[i])) return false;
    }

    for (size_t i = 0; i < len; ++i) {
        int d = num[len - 1 - i] - '0';
        if (i % 2 != 0) {
            d *= 2;
            if (d > 9) d -= 9;
        }
        csum += d;
    }

    return (csum % 10) == 0;
}