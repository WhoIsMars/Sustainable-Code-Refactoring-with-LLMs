#include "isbn_verifier.h"

using std::string;

auto constexpr digit = [](const char c) noexcept -> int {
    if (c == 'X') return 10;
    if (isdigit(c)) return c - '0';
    return -1;
};

bool isbn_verifier::is_valid(string const& isbn) noexcept {
    int position {10}, csum {0};
    auto valid_checksum = [&](string num) {
        for (auto &c: num) {
            if (c == '-') continue;
            if (digit(c) == -1) break;
            if (digit(c) == 10 && position != 1) break;
            csum += digit(c) * position--;
        }
        return position == 0 && !(csum % 11);
    };
    return valid_checksum(isbn);
}
