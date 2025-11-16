#include "trinary.h"
#include <algorithm>

auto valid(std::string const &trinary) noexcept -> bool {
    return std::all_of(trinary.begin(), trinary.end(), [](char d) {
        return (d == std::clamp(d, '0', '2'));
    });
}

int trinary::to_decimal(const std::string &trinary) noexcept {
    if (!valid(trinary)) return 0;
    int decimal { 0 };
    for (auto d = trinary.begin(); d < trinary.end(); ++d) {
        decimal += (decimal << 1) + *d - '0';
    }
    return decimal;
}