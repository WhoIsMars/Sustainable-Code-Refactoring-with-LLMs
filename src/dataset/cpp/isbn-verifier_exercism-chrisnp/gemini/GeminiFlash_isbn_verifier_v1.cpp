#include "isbn_verifier.h"

#include <cctype>  // Required for std::isdigit
#include <numeric> // Required for std::accumulate

using std::string;

bool isbn_verifier::is_valid(string const& isbn) noexcept {
    int sum = 0;
    int count = 0;
    int position = 10;

    for (char c : isbn) {
        if (c == '-') continue;

        int d;
        if (std::isdigit(c)) {
            d = c - '0';
        } else if (c == 'X' && count == 9) {
            d = 10;
        } else {
            return false; // Invalid character
        }

        sum += d * position;
        position--;
        count++;
    }

    return (count == 10) && (sum % 11 == 0);
}