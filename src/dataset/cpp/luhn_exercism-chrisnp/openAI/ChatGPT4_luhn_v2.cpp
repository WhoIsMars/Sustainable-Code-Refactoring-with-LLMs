#include "luhn.h"
#include <cctype>

using namespace std;

bool luhn::valid(const string& num) {
    int csum = 0;
    bool alternate = false;
    int len = num.length();

    if (len < 2) return false;

    for (int i = len - 1; i >= 0; --i) {
        char c = num[i];
        if (c == ' ') continue;
        if (!isdigit(c)) return false;

        int d = c - '0';
        if (alternate) {
            d *= 2;
            if (d > 9) d -= 9;
        }
        csum += d;
        alternate = !alternate;
    }

    return csum % 10 == 0;
}