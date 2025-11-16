#include "isbn_verifier.h"
#include <cctype>

using std::string;

auto constexpr digit = [](char c) noexcept -> int {
    return (c == 'X') ? 10 : (std::isdigit(c) ? c - '0' : -1);
};

bool isbn_verifier::is_valid(string const& isbn) noexcept {
    int position = 10, csum = 0;
    for (char c : isbn) {
        if (c == '-') continue;
        int d = digit(c);
        if (d == -1 || (d == 10 && position != 1)) return false;
        csum += d * position--;
    }
    return position == 0 && csum % 11 == 0;
}