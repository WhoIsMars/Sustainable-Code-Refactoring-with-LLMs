#include "say.h"

#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace say {

const std::vector<std::string> to_ten{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

const std::vector<std::string> teens{"padd", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

const std::vector<std::string> tenners{"padd", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety", "hundred"};       
    
const std::vector<std::string> potences{"padd", "billion", "million", "thousand"};


std::vector<int> break_up(long long i) {
    std::vector<int> number_thousands;
    number_thousands.reserve(4);

    long long divisor = 1000000000;
    for (int j = 0; j < 4; ++j) {
        int quotient = i / divisor;
        number_thousands.push_back(quotient);
        i %= divisor;
        divisor /= 1000;
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

    for (size_t index = 0; index < chunks.size(); ++index) {
        int chunk = chunks[index];
        if (chunk == 0) continue;

        int chunk_100th = chunk / 100;
        int quotient = chunk % 100;

        if (chunk_100th) {
            out += to_ten[chunk_100th] + " hundred";
            if (quotient != 0) {
                out += " " + in_english_100(quotient);
            }
        } else {
            out += in_english_100(quotient);
        }

        if (index < 3) {
            out += " " + potences[3 - index];
        }

        if (index < 3 && (chunks[index+1] != 0)) {
            out += " ";
        }
    }

    return out;
}



std::string in_english_100(int i) {
    if (i < 10) return to_ten[i];
    if (i < 20) return teens[i - 10 + 1];

    int quotient = i / 10;
    int remainder = i % 10;

    if (remainder == 0) return tenners[quotient];

    return tenners[quotient] + "-" + to_ten[remainder];
}




}  // namespace say