#include "beer_song.h"
#include <string>

namespace {
    constexpr const char* const VERSE_TEMPLATES[] = {
        "No more bottles of beer on the wall, no more bottles of beer.\n"
        "Go to the store and buy some more, 99 bottles of beer on the wall.\n",
        
        "1 bottle of beer on the wall, 1 bottle of beer.\n"
        "Take it down and pass it around, no more bottles of beer on the wall.\n",
        
        "2 bottles of beer on the wall, 2 bottles of beer.\n"
        "Take one down and pass it around, 1 bottle of beer on the wall.\n"
    };
    
    std::string format_verse(int n) {
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

std::string beer_song::verse(int n) noexcept {
    if (n <= 2) {
        return VERSE_TEMPLATES[n];
    }
    return format_verse(n);
}

std::string beer_song::sing(int start, int end) noexcept {
    std::string result;
    const size_t estimated_size = (start - end + 1) * 80;
    result.reserve(estimated_size);
    
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