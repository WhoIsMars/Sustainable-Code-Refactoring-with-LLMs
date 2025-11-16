#include "isbn_verifier.h"

#include <cctype>  // Required for std::isdigit

using std::string;

bool isbn_verifier::is_valid(string const& isbn) noexcept {
    int position = 10;
    int csum = 0;
    int count = 0;

    for (char c : isbn) {
        if (c == '-') continue;

        if (std::isdigit(c)) {
            csum += (c - '0') * position;
            position--;
            count++;
        } else if (c == 'X' && position == 1) {
            csum += 10 * position;
            position--;
            count++;
        } else {
            return false; // Invalid character
        }

        if (position < 1) break; // Optimization: Stop early if position goes below 1
    }

    return (position == 0 && count == (int)isbn.size() - (int)std::count(isbn.begin(), isbn.end(), '-')) && (csum % 11 == 0);
}