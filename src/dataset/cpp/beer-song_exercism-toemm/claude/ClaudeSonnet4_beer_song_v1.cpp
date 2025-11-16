#include "beer_song.h"

#include <string>

namespace beer_song {

std::string verse(int i) {
    if (i == 0) {
        return "No more bottles of beer on the wall, no more bottles of beer.\n"
               "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
    }

    std::string result;
    result.reserve(120); // Pre-allocate reasonable capacity
    
    const std::string num_str = std::to_string(i);
    const bool is_one = (i == 1);
    const bool is_two = (i == 2);
    
    result += num_str;
    result += is_one ? " bottle" : " bottles";
    result += " of beer on the wall, ";
    result += num_str;
    result += is_one ? " bottle" : " bottles";
    result += " of beer.\nTake ";
    result += is_one ? "it" : "one";
    result += " down and pass it around, ";
    
    if (is_one) {
        result += "no more bottle";
    } else {
        result += std::to_string(i - 1);
        result += is_two ? " bottle" : " bottles";
    }
    
    result += " of beer on the wall.\n";
    
    return result;
}

std::string sing(int begin, int ending) {
    std::string result;
    
    // Pre-calculate total size to minimize reallocations
    size_t estimated_size = (begin - ending + 1) * 120;
    if (begin != ending) {
        estimated_size += (begin - ending); // for newlines
    }
    result.reserve(estimated_size);
    
    for (int i = begin; i >= ending; --i) {
        result += verse(i);
        if (i != ending) {
            result += '\n';
        }
    }
    
    return result;
}

}  // namespace beer_song