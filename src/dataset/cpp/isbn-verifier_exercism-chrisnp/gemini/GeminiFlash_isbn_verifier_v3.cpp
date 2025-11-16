#include "isbn_verifier.h"
#include <cctype>

using std::string;

bool isbn_verifier::is_valid(string const& isbn) noexcept {
    int position = 10;
    int csum = 0;
    int len = isbn.length();
    int i = 0;

    while (i < len && position > 0) {
        char c = isbn[i];
        if (c == '-') {
            i++;
            continue;
        }

        int d;
        if (isdigit(c)) {
            d = c - '0';
        } else if (c == 'X' && position == 1) {
            d = 10;
        } else {
            return false;
        }

        csum += d * position;
        position--;
        i++;
    }

    return position == 0 && (csum % 11 == 0);
}