#include "say.h"

#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace say {

const std::vector<std::string> to_ten{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

const std::vector<std::string> teens{"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

const std::vector<std::string> tenners{"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};       
    
const std::vector<std::string> potences{"", "billion", "million", "thousand"};


std::vector<int> break_up(long long i) {
    std::vector<int> number_thousands;
    number_thousands.reserve(4); // Pre-allocate memory

    long long divisor = 1000000000;
    for (int j = 0; j < 3; ++j) {
        int quotient = i / divisor;
        number_thousands.push_back(quotient);
        i %= divisor;
        divisor /= 1000;
    }
    number_thousands.push_back(static_cast<int>(i)); // Last chunk
    return number_thousands;
}


std::string in_english(long long i) {
    if (i < 0 || i >= 1000000000000) {
        throw std::domain_error("invalid number.");
    }

    if (i < 100) {
        return in_english_100(static_cast<int>(i));
    }

    std::vector<int> chunks = break_up(i);
    std::string out;

    for (size_t index = 0; index < chunks.size(); ++index) {
        int chunk = chunks[index];
        if (chunk == 0) continue;

        std::string chunk_str = in_english_100(chunk);
        out += chunk_str;

        if (index < 3) {
            out += " " + potences[3 - index];
        }

        if (index < 3 && chunk != 0) {
            out += " ";
        }
    }

    // Remove trailing space if any
    if (!out.empty() && out.back() == ' ') {
        out.pop_back();
    }

    return out;
}



std::string in_english_100(int i) {
    if (i < 10) {
        return to_ten[i];
    }

    if (i < 20) {
        return teens[i - 11];
    }

    int quotient = i / 10;
    int remainder = i % 10;

    if (remainder == 0) {
        return tenners[quotient];
    }

    return tenners[quotient] + "-" + to_ten[remainder];
}

}  // namespace say