#include "beer_song.h"
#include <string>
#include <array>

namespace {

constexpr std::array<const char*, 3> special_verses = {
    "No more bottles of beer on the wall, no more bottles of beer.\nGo to the store and buy some more, 99 bottles of beer on the wall.\n",
    "1 bottle of beer on the wall, 1 bottle of beer.\nTake it down and pass it around, no more bottles of beer on the wall.\n",
    "2 bottles of beer on the wall, 2 bottles of beer.\nTake one down and pass it around, 1 bottle of beer on the wall.\n"
};

} // namespace

std::string beer_song::verse(int n) noexcept {
    if (n >= 0 && n <= 2) {
        switch (n) {
            case 0: return special_verses[0];
            case 1: return special_verses[1];
            case 2: return special_verses[2];
        }
    }

    std::string result;
    result.reserve(128); 

    result += std::to_string(n);
    result += " bottles of beer on the wall, ";
    result += std::to_string(n);
    result += " bottles of beer.\nTake one down and pass it around, ";
    result += std::to_string(n - 1);
    result += " bottles of beer on the wall.\n";

    return result;
}

std::string beer_song::sing(int start, int end) noexcept {
    std::string verses;
    verses.reserve((start - end + 1) * 200);

    for (int n = start; n >= end; --n) {
        if (n != start) {
            verses += '\n';
        }
        verses += verse(n);
    }
    return verses;
}

std::string beer_song::sing(int start) noexcept {
    return sing(start, 0);
}