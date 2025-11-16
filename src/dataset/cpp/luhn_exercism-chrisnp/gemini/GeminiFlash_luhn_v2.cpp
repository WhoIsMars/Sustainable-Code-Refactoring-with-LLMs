#include "luhn.h"
#include <algorithm>
#include <cctype>

using namespace std;

bool luhn::valid(string num) {
    int len = 0;
    for (char c : num) {
        if (c != ' ') {
            num[len++] = c;
        }
    }
    if (len < 2) return false;

    int csum = 0;
    for (int i = len - 1, j = 0; i >= 0; --i, ++j) {
        if (isdigit(num[i])) {
            int d = num[i] - '0';
            if (j % 2 != 0) {
                d *= 2;
                if (d > 9) {
                    d -= 9;
                }
            }
            csum += d;
        } else {
            return false;
        }
    }
    return (csum % 10) == 0;
}