#include "say.h"

#include <string>
#include <vector>
#include <stdexcept>

namespace say {

constexpr const char* to_ten[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

constexpr const char* teens[] = {"", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

constexpr const char* tenners[] = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};       
    
constexpr const char* potences[] = {"", "billion", "million", "thousand"};

std::vector<int> break_up(long long i) {
    std::vector<int> number_thousands;
    number_thousands.reserve(4);
    
    constexpr long long divisors[] = {1000000000, 1000000, 1000, 1};
    
    for (long long divisor : divisors) {
        int quotient = static_cast<int>(i / divisor);
        number_thousands.push_back(quotient);
        if (quotient != 0) {
            i %= divisor;
        }
    }
    return number_thousands;
}

std::string in_english(long long i) {
    if (i >= 0 && i < 100) {
        return in_english_100(static_cast<int>(i));
    }
    
    if (i < 0 || i >= 1000000000000) {
        throw std::domain_error("invalid number.");
    }
    
    std::vector<int> chunks = break_up(i);
    std::string out;
    out.reserve(256);
    
    for (std::size_t index = 0; index < chunks.size(); ++index) {
        int chunk = chunks[index];
        
        if (chunk == 0) continue;
        
        if (!out.empty()) {
            out += " ";
        }
        
        int chunk_100th = chunk / 100;
        int quotient = chunk % 100;
        
        if (chunk_100th > 0) {
            out += to_ten[chunk_100th];
            out += " hundred";
            if (quotient > 0) {
                out += " ";
            }
        }
        
        if (quotient > 0) {
            out += in_english_100(quotient);
        }
        
        if (index < 3) {
            out += " ";
            out += potences[index + 1];
        }
    }
    
    return out;
}

std::string in_english_100(int i) {
    if (i < 10) {
        return to_ten[i];
    }
    
    int quotient = i / 10;
    int remainder = i % 10;
    
    if (quotient == 1 && remainder > 0) {
        return teens[remainder];
    }
    
    std::string result = tenners[quotient];
    
    if (remainder > 0) {
        result += "-";
        result += to_ten[remainder];
    }
    
    return result;
}

}  // namespace say