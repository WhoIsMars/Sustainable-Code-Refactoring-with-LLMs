#include "beer_song.h"
#include <string>

namespace {
    constexpr const char* const VERSE_0 = 
        "No more bottles of beer on the wall, "
        "no more bottles of beer.\nGo "
        "to the store and buy some more, "
        "99 bottles of beer on the wall.\n";
    
    constexpr const char* const VERSE_1 = 
        "1 bottle of beer on the wall, "
        "1 bottle of beer.\nTake it down and "
        "pass it around, no more bottles "
        "of beer on the wall.\n";
    
    constexpr const char* const VERSE_2 = 
        "2 bottles of beer on the wall, "
        "2 bottles of beer.\nTake one down "
        "and pass it around, 1 bottle "
        "of beer on the wall.\n";
}

std::string beer_song::verse(int n) noexcept {
    switch (n) {
        case 0:
            return VERSE_0;
        case 1:
            return VERSE_1;
        case 2:
            return VERSE_2;
        default: {
            std::string result;
            result.reserve(80);
            result += std::to_string(n);
            result += " bottles of beer on the wall, ";
            result += std::to_string(n);
            result += " bottles of beer.\nTake one down and pass it around, ";
            result += std::to_string(n - 1);
            result += " bottles of beer on the wall.\n";
            return result;
        }
    }
}

std::string beer_song::sing(int start, int end) noexcept {
    std::string result;
    const int verse_count = start - end + 1;
    result.reserve(verse_count * 80);
    
    for (int n = start; n >= end; --n) {
        if (n != start) {
            result += '\n';
        }
        result += verse(n);
    }
    return result;
}

std::string beer_song::sing(int start) noexcept {
    return sing(start, 0);
}