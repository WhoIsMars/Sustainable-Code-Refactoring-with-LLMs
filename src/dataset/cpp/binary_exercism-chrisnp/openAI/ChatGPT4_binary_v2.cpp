#include "binary.h"
#include <cctype>

using std::string;

long binary::convert(const string& binstr) noexcept {
    long decimal = 0;
    for (char d : binstr) {
        if (d != '0' && d != '1') return 0;
        decimal = (decimal << 1) + (d - '0');
    }
    return decimal;
}