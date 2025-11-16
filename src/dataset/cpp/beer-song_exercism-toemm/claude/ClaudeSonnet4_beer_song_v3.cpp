#include "beer_song.h"

#include <string>

namespace beer_song {

std::string verse(int i) {
    if (i == 0) {
        return "No more bottles of beer on the wall, no more bottles of beer.\n"
               "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
    }

    const char* bottle_word = (i == 1) ? " bottle" : " bottles";
    const char* take_word = (i == 1) ? "it" : "one";
    
    std::string result;
    result.reserve(120);
    
    result += std::to_string(i);
    result += bottle_word;
    result += " of beer on the wall, ";
    result += std::to_string(i);
    result += bottle_word;
    result += " of beer.\nTake ";
    result += take_word;
    result += " down and pass it around, ";
    
    if (i == 1) {
        result += "no more bottles";
    } else {
        result += std::to_string(i - 1);
        result += (i == 2) ? " bottle" : " bottles";
    }
    
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