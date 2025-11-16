#include "beer_song.h"
#include <string>

std::string beer_song::verse(int n) noexcept {
    if (n == 0) {
        return "No more bottles of beer on the wall, no more bottles of beer.\nGo to the store and buy some more, 99 bottles of beer on the wall.\n";
    } else if (n == 1) {
        return "1 bottle of beer on the wall, 1 bottle of beer.\nTake it down and pass it around, no more bottles of beer on the wall.\n";
    } else if (n == 2) {
        return "2 bottles of beer on the wall, 2 bottles of beer.\nTake one down and pass it around, 1 bottle of beer on the wall.\n";
    } else {
        std::string verse_str = std::to_string(n) + " bottles of beer on the wall, " + std::to_string(n) + " bottles of beer.\nTake one down and pass it around, " + std::to_string(n - 1) + " bottles of beer on the wall.\n";
        return verse_str;
    }
}

std::string beer_song::sing(int start, int end) noexcept {
    std::string verses;
    for (int n = start; n >= end; --n) {
        verses += verse(n);
        if (n != end) {
            verses += '\n';
        }
    }
    return verses;
}

std::string beer_song::sing(int start) noexcept {
    return sing(start, 0);
}