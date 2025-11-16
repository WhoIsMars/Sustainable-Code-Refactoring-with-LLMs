#include "say.h"

#include <string>
#include <vector>
#include <stdexcept>
#include <array>

namespace say {

const std::array<std::string, 10> to_ten{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const std::array<std::string, 10> teens{"", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const std::array<std::string, 11> tenners{"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety", "hundred"};
const std::array<std::string, 4> potences{"", "billion", "million", "thousand"};

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
    if (i < 20) return teens[i % 10];
    if (i % 10 == 0) return tenners[i / 10];
    return tenners[i / 10] + "-" + to_ten[i % 10];
}

std::string in_english(long long i) {
    if (i < 0 || i >= 1'000'000'000'000) throw std::domain_error("invalid number.");
    if (i < 100) return in_english_100(i);

    std::vector<int> chunks = break_up(i);
    std::string out;

    for (std::size_t index = 0; index < chunks.size(); ++index) {
        int chunk = chunks[index];
        if (chunk == 0) continue;

        if (chunk >= 100) {
            out += to_ten[chunk / 100] + " hundred";
            if (chunk % 100 != 0) out += " " + in_english_100(chunk % 100);
        } else {
            out += in_english_100(chunk);
        }

        if (index < potences.size() && !potences[index].empty()) {
            out += " " + potences[index];
        }

        if (index < chunks.size() - 1) out += " ";
    }

    return out;
}

}  // namespace say