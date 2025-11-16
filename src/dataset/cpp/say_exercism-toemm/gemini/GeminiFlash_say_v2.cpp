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
    number_thousands.reserve(4);

    for (long long j = 1000000000; j > 0; j /= 1000) {
        int quotient = i / j;
        if (quotient > 0) {
            number_thousands.push_back(quotient);
            i %= j;
        } else {
            number_thousands.push_back(0);
        }
    }
    
    while (number_thousands.front() == 0 && number_thousands.size() > 1) {
        number_thousands.erase(number_thousands.begin());
    }

    return number_thousands;
}


std::string in_english(long long i) {
    if (i < 0 || i >= 1000000000000) {
        throw std::domain_error("invalid number.");
    }

    if (i < 100) {
        return in_english_100(i);
    }

    std::vector<int> chunks = break_up(i);
    std::string out;
    std::size_t chunks_size = chunks.size();

    for (std::size_t index = 0; index < chunks_size; ++index) {
        int chunk = chunks[index];
        if (chunk == 0) continue;

        std::string chunk_str = in_english_100(chunk);
        out += chunk_str;

        if (index < chunks_size - 1) {
            out += " " + potences[chunks_size - 1 - index] + " ";
        } else {
            out += " " + potences[chunks_size - 1 - index];
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