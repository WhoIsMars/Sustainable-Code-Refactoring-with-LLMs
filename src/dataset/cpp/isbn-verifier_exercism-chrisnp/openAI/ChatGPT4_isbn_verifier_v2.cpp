#include "isbn_verifier.h"

using std::string;

constexpr int digit(const char c) noexcept {
    return (c == 'X') ? 10 : (isdigit(c) ? c - '0' : -1);
}

bool isbn_verifier::is_valid(const string& isbn) noexcept {
    int position = 10, csum = 0;

    for (const char c : isbn) {
        if (c == '-') continue;
        int d = digit(c);
        if (d == -1 || (d == 10 && position != 1)) return false;
        csum += d * position--;
    }

    return position == 0 && csum % 11 == 0;
}