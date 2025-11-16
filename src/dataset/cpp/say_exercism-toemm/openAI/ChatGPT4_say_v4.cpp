#include "say.h"

#include <string>
#include <vector>
#include <stdexcept>
#include <array>

namespace say {

constexpr std::array<const char*, 10> to_ten{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
constexpr std::array<const char*, 10> teens{"", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
constexpr std::array<const char*, 11> tenners{"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety", "hundred"};
constexpr std::array<const char*, 4> potences{"", "billion", "million", "thousand"};

std::vector<int> break_up(long long i) {
    std::vector<int> number_thousands;
    for (long long j = 1'000'000'000'000; j > 0; j /= 1'000) {
        number_thousands.emplace_back(i / j);
        i %= j;
    }
    return number_thousands;
}

std::string in_english_100(int i) {
    if (i < 10) return to_ten[i];
    if (i < 20) return teens[i - 10];
    int quotient = i / 10, remainder = i % 10;
    return remainder == 0 ? tenners[quotient] : std::string(tenners[quotient]) + "-" + to_ten[remainder];
}

std::string in_english(long long i) {
    if (i < 0 || i >= 1'000'000'000'000) throw std::domain_error("invalid number.");
    if (i < 100) return in_english_100(i);

    std::vector<int> chunks = break_up(i);
    std::string out;
    size_t chunks_size = chunks.size();

    for (size_t index = 0; index < chunks_size; ++index) {
        int chunk = chunks[index];
        if (chunk == 0) continue;

        int chunk_100th = chunk / 100, quotient = chunk % 100;
        if (chunk_100th) {
            out += to_ten[chunk_100th] + std::string(" hundred");
            if (quotient) out += " " + in_english_100(quotient);
        } else {
            out += in_english_100(quotient);
        }

        if (index < chunks_size - 1 && !potences[chunks_size - 1 - index].empty()) {
            out += " " + std::string(potences[chunks_size - 1 - index]);
        }

        if (index < chunks_size - 1) out += " ";
    }

    return out;
}

}  // namespace say