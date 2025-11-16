#include "say.h"

#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>

namespace say {

const std::vector<std::string> to_ten{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const std::vector<std::string> teens{"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const std::vector<std::string> tenners{"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
const std::vector<std::string> potences{"billion", "million", "thousand"};

std::vector<int> break_up(long long i) {
    std::vector<int> number_thousands;
    for (long long j = 1000000000; j > 0; j /= 1000) {
        number_thousands.push_back(i / j);
        i %= j;
    }
    return number_thousands;
}

std::string in_english_100(int i) {
    if (i < 10) return to_ten[i];
    if (i < 20) return i == 10 ? tenners[1] : teens[i - 11];
    int quotient = i / 10, remainder = i % 10;
    return remainder == 0 ? tenners[quotient] : tenners[quotient] + "-" + to_ten[remainder];
}

std::string in_english(long long i) {
    if (i < 0 || i >= 1000000000000) throw std::domain_error("invalid number.");
    if (i < 100) return in_english_100(i);

    std::vector<int> chunks = break_up(i);
    std::ostringstream out;
    bool first_chunk = true;

    for (size_t index = 0; index < chunks.size(); ++index) {
        int chunk = chunks[index];
        if (chunk == 0) continue;

        if (!first_chunk) out << " ";
        first_chunk = false;

        int chunk_100th = chunk / 100;
        int remainder = chunk % 100;

        if (chunk_100th) {
            out << to_ten[chunk_100th] << " hundred";
            if (remainder) out << " " << in_english_100(remainder);
        } else {
            out << in_english_100(remainder);
        }

        if (index < potences.size() && chunks[index + 1] != 0) {
            out << " " << potences[potences.size() - index - 1];
        } else if (index < potences.size()) {
            out << " " << potences[potences.size() - index - 1];
        }
    }

    return out.str();
}

}  // namespace say