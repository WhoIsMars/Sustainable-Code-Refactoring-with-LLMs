#include "luhn.h"
#include <algorithm>

using namespace std;

bool luhn::valid( string num ) {
    num.erase(remove(num.begin(), num.end(), ' '), num.end());
    if (num.length() < 2) return false;
    int csum { 0 };
    reverse(num.begin(), num.end());
    for (unsigned int i = 0; i < num.length(); ++i) {
        if (isdigit(num[i])) {
            int d = int( num[i] ) - '0';
            csum += i % 2 != 0 ? (d > 4 ? (d * 2) - 9 : d * 2) : d;
        }
        else return false;
    }
    return !(csum % 10);
}
