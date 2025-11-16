#include "say.h"

#include <string>
#include <array>
#include <stdexcept>

namespace say {

constexpr std::array<const char*, 10> to_ten{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

constexpr std::array<const char*, 10> teens{"", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

constexpr std::array<const char*, 11> tenners{"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety", "hundred"};       
    
constexpr std::array<const char*, 4> potences{"", "billion", "million", "thousand"};

std::array<int, 4> break_up(long long i) {
    std::array<int, 4> number_thousands{};
    
    constexpr std::array<long long, 4> divisors{1000000000, 1000000, 1000, 1};
    
    for (int j = 0; j < 4; ++j) {
        number_thousands[j] = static_cast<int>(i / divisors[j]);
        i %= divisors[j];
    }
    
    return number_thousands;
}

std::string in_english(long long i) {
    if (i < 0 || i >= 1000000000000) {
        throw std::domain_error("invalid number.");
    }
    
    if (i < 100) {
        return in_english_100(static_cast<int>(i));
    }
    
    auto chunks = break_up(i);
    std::string out;
    out.reserve(256);
    
    for (int index = 0; index < 4; ++index) {
        int chunk = chunks[index];
        
        if (chunk == 0) continue;
        
        if (!out.empty()) {
            out += ' ';
        }
        
        int chunk_100th = chunk / 100;
        int quotient = chunk % 100;
        
        if (chunk_100th > 0) {
            out += to_ten[chunk_100th];
            out += " hundred";
            if (quotient > 0) {
                out += ' ';
            }
        }
        
        if (quotient > 0) {
            out += in_english_100(quotient);
        }
        
        if (index < 3) {
            out += ' ';
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
    
    if (remainder == 0) {
        return tenners[quotient];
    }
    
    if (quotient == 1) {
        return teens[remainder];
    }
    
    std::string result;
    result.reserve(32);
    result += tenners[quotient];
    result += '-';
    result += to_ten[remainder];
    
    return result;
}

}  // namespace say