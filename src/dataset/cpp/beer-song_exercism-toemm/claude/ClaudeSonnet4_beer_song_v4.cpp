#include "beer_song.h"

#include <string>

namespace beer_song {

std::string verse(int i) {
    if (i == 0) {
        return "No more bottles of beer on the wall, no more bottles of beer.\n"
               "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
    }

    std::string result;
    result.reserve(120);
    
    const bool is_one = (i == 1);
    const bool is_two = (i == 2);
    const std::string count = std::to_string(i);
    const std::string next_count = is_one ? "no more" : std::to_string(i - 1);
    
    result += count;
    result += is_one ? " bottle" : " bottles";
    result += " of beer on the wall, ";
    result += count;
    result += is_one ? " bottle" : " bottles";
    result += " of beer.\nTake ";
    result += is_one ? "it" : "one";
    result += " down and pass it around, ";
    result += next_count;
    result += " bottle";
    result += is_two ? "" : "s";
    result += " of beer on the wall.\n";
    
    return result;
}

std::string sing(int begin, int ending) {
    std::string result;
    const int verse_count = begin - ending + 1;
    result.reserve(verse_count * 120);
    
    for (int i = begin; i >= ending; --i) {
        result += verse(i);
        if (i != ending) {
            result += '\n';
        }
    }
    
    return result;
}

}  // namespace beer_song