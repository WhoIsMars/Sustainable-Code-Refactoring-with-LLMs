#include "beer_song.h"
#include <string>

std::string beer_song::verse(int n) noexcept {
    static const std::string case0 = "No more bottles of beer on the wall, "
                                    "no more bottles of beer.\nGo "
                                    "to the store and buy some more, "
                                    "99 bottles of beer on the wall.\n";
    static const std::string case1 = "1 bottle of beer on the wall, "
                                    "1 bottle of beer.\nTake it down and "
                                    "pass it around, no more bottles "
                                    "of beer on the wall.\n";
    static const std::string case2 = "2 bottles of beer on the wall, "
                                    "2 bottles of beer.\nTake one down "
                                    "and pass it around, 1 bottle "
                                    "of beer on the wall.\n";
    
    switch (n) {
        case 0: return case0;
        case 1: return case1;
        case 2: return case2;
        default:
            return std::to_string(n) + " bottles of beer on the wall, " +
                   std::to_string(n) + " bottles of beer.\n"
                   "Take one down and pass it around, " +
                   std::to_string(n - 1) + " bottles of beer on the wall.\n";
    }
}

std::string beer_song::sing(int start, int end) noexcept {
    std::string result;
    result.reserve((start - end + 1) * 120); // Approximate verse length
    
    for (int n = start; n >= end; --n) {
        if (n != start) result += '\n';
        result += verse(n);
    }
    return result;
}

std::string beer_song::sing(int start) noexcept {
    return sing(start, 0);
}