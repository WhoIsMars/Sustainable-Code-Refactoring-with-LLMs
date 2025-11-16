#include "isbn_verifier.h"

using std::string;

bool isbn_verifier::is_valid(string const& isbn) noexcept {
    int position = 10;
    int csum = 0;
    int len = isbn.length();
    int d;

    for (int i = 0; i < len; ++i) {
        char c = isbn[i];
        if (c == '-') continue;

        if (isdigit(c)) {
            d = c - '0';
        } else if (c == 'X' && position == 1) {
            d = 10;
        } else {
            return false;
        }

        csum += d * position;
        --position;

        if (position < 0) return false;
    }

    return position == 0 && (csum % 11 == 0);
}