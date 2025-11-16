#include "say.h"

#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace say {

const std::vector<std::string> to_ten{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

const std::vector<std::string> teens{"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

const std::vector<std::string> tenners{"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

const std::vector<std::string> potences{"billion", "million", "thousand"};


std::string in_english(long long i) {
    if (i < 0 || i >= 1000000000000) {
        throw std::domain_error("invalid number.");
    }

    if (i < 100) {
        return in_english_100(i);
    }

    std::string out;
    std::vector<int> chunks;
    
    long long remaining = i;
    for (int j = 1000000000; j >= 1000; j /= 1000) {
        chunks.push_back(remaining / j);
        remaining %= j;
    }
    chunks.push_back(remaining);

    size_t chunk_index = 0;
    for (size_t index = 0; index < chunks.size(); ++index) {
        int chunk = chunks[index];
        if (chunk == 0) continue;

        std::string chunk_str = in_english_100(chunk);
        out += chunk_str;

        if (index < 3) {
            out += " " + potences[index];
        }

        if (index < 3 && remaining > 0 && chunk != 0) {
            out += " ";
        }
    }

    return out;
}


std::string in_english_100(int i) {
    if (i < 10) {
        return to_ten[i];
    } else if (i < 20) {
        return teens[i - 11];
    } else {
        int quotient = i / 10;
        int remainder = i % 10;

        if (remainder == 0) {
            return tenners[quotient];
        } else {
            return tenners[quotient] + "-" + to_ten[remainder];
        }
    }
}

}  // namespace say