#include "say.h"

#include <string>
#include <array>
#include <stdexcept>

namespace say {

constexpr std::array<const char*, 10> to_ten{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

constexpr std::array<const char*, 10> teens{"", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

constexpr std::array<const char*, 10> tenners{"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};       
    
constexpr std::array<const char*, 4> potences{"", "billion", "million", "thousand"};

std::string in_english_100(int i) {
    if (i == 0) return to_ten[0];
    
    int quotient = i / 10;
    int remainder = i % 10;
    
    if (quotient == 0) return to_ten[i];
    if (remainder == 0) return tenners[quotient];
    if (quotient == 1) return teens[remainder];
    
    std::string result;
    result.reserve(32);
    result += tenners[quotient];
    result += '-';
    result += to_ten[remainder];
    return result;
}

std::string in_english(long long i) {
    if (i < 0 || i >= 1000000000000LL) {
        throw std::domain_error("invalid number.");
    }
    
    if (i < 100) {
        return in_english_100(static_cast<int>(i));
    }
    
    std::string result;
    result.reserve(256);
    
    constexpr long long divisors[] = {1000000000LL, 1000000LL, 1000LL, 1LL};
    
    bool first_chunk = true;
    
    for (int idx = 0; idx < 4; ++idx) {
        long long divisor = divisors[idx];
        int chunk = static_cast<int>(i / divisor);
        
        if (chunk == 0) continue;
        
        if (!first_chunk) {
            result += ' ';
        }
        first_chunk = false;
        
        int hundreds = chunk / 100;
        int remainder = chunk % 100;
        
        if (hundreds > 0) {
            result += to_ten[hundreds];
            result += " hundred";
            if (remainder > 0) {
                result += ' ';
            }
        }
        
        if (remainder > 0) {
            result += in_english_100(remainder);
        }
        
        if (idx < 3) {
            result += ' ';
            result += potences[idx + 1];
        }
        
        i %= divisor;
    }
    
    return result;
}

}  // namespace say