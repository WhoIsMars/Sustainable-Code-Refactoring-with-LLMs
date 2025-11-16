#include "beer_song.h"
#include <string>

std::string beer_song::verse(int n) noexcept {
    if (n == 0) {
        return "No more bottles of beer on the wall, no more bottles of beer.\n"
               "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
    } else if (n == 1) {
        return "1 bottle of beer on the wall, 1 bottle of beer.\n"
               "Take it down and pass it around, no more bottles of beer on the wall.\n";
    } else if (n == 2) {
        return "2 bottles of beer on the wall, 2 bottles of beer.\n"
               "Take one down and pass it around, 1 bottle of beer on the wall.\n";
    } else {
        return std::to_string(n) + " bottles of beer on the wall, " + std::to_string(n) +
               " bottles of beer.\nTake one down and pass it around, " +
               std::to_string(n - 1) + " bottles of beer on the wall.\n";
    }
}

std::string beer_song::sing(int start, int end) noexcept {
    std::string result;
    for (int n = start; n >= end; --n) {
        if (!result.empty()) result += '\n';
        result += verse(n);
    }
    return result;
}

std::string beer_song::sing(int start) noexcept {
    return sing(start, 0);
}