#include "say.h"

#include <string>
#include <vector>
#include <stdexcept>

namespace say {

const std::vector<std::string> to_ten{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

const std::vector<std::string> teens{"padd", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

const std::vector<std::string> tenners{"padd", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety", "hundred"};       
    
const std::vector<std::string> potences{"padd", "billion", "million", "thousand"};


std::vector<int> break_up(long long i) {

    // 1234567890 should yield a list like 1, 234, 567, and 890
    // 1523 1

    std::vector<int> number_thousands{};


    for (long long int j{1000000000000}; j != 0; j /= 1000) {
        int quotient = i / j;
        number_thousands.emplace_back(quotient);

        // big enough number
        if (quotient != 0) i %= j;

    }
    return number_thousands;
}


std::string in_english(long long i) {

    std::vector<int> chunks{};
    std::string out{};

    if (i >= 0 && i < 100)
        return in_english_100(i);
    else if (i >= 100 && i < 1000000000000) 
        chunks = break_up(i);
    else   
        throw std::domain_error("invalid number.");

    int chunk{};
    int chunk_100th{};
    int quotient{};
    std::size_t chunks_size{chunks.size()};

    // pad chunk by 1 so you can index like other vectors
    chunks.insert(chunks.begin(), 9999);

    for (std::size_t index{1}; index <= chunks_size; index++) {
        chunk = chunks[index];

        if (chunk == 0) continue;

        // normal case
        // '123 billion 234 million 567 thousand 890' 
        // 1 thousand (0, 0, 0, 1, 0)
        else {
            chunk_100th = chunk / 100;
            quotient = chunk % 100;

            // 100 billion
            if (chunk_100th && quotient == 0) {
                out += to_ten[chunk_100th];
                (index <= 4) ? out += " hundred " : out += " hundred";
            // 123 billion
            } else if (chunk_100th && quotient != 0) {
                out += to_ten[chunk_100th];
                out += " hundred ";
                (index <= 4) ? out += in_english_100(quotient) + " " : out += in_english_100(quotient);
            // 12 billion
            } else {
                out += in_english_100(quotient) + " ";
            }

            // if it's not the last hundred then add potence
            // add space if there is values left afterwards
            // emit space if not
            if (index <= 4) {
                if (!chunks[chunks_size])
                    out += potences[index-1];
                else
                    out += potences[index-1] + " ";
            }
            
        }


    }

    return out;

}



std::string in_english_100(int i) {

    int remainder{};
    int quotient{};
    std::string out{};


    // quotient first: i.e. 34/100 = 3 "thirty"
    quotient = i / 10;
    remainder = i % 10;

    // 0-9
    if (quotient == 0) return to_ten[i];

    // 10, 20, 30, ... 100
    if (remainder == 0) return tenners[quotient];

    // 11-19
    if (quotient == 1) return teens[remainder];

    // everything else, i.e. 34
    return out + tenners[quotient] + "-" + to_ten[remainder];
}




}  // namespace say
