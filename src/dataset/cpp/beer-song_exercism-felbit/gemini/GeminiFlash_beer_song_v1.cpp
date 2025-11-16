#include "beer_song.h"
#include <array>

std::string beer::verse(const short bottles) {
    switch (bottles) {
        case 0:
            return "No more bottles of beer on the wall, no more bottles of beer.\nGo to the store and buy some more, 99 bottles of beer on the wall.\n";
        case 1:
            return "1 bottle of beer on the wall, 1 bottle of beer.\nTake it down and pass it around, no more bottles of beer on the wall.\n";
        case 2:
            return "2 bottles of beer on the wall, 2 bottles of beer.\nTake one down and pass it around, 1 bottle of beer on the wall.\n";
        default: {
            std::string verse_str = std::to_string(bottles) + " bottles of beer on the wall, " + std::to_string(bottles) + " bottles of beer.\nTake one down and pass it around, " + std::to_string(bottles - 1) + " bottles of beer on the wall.\n";
            return verse_str;
        }
    }
}

std::string beer::sing(const short start, const short end) {
    std::string song;
    song.reserve((start - end + 1) * 200); // Pre-allocate memory to avoid reallocations

    for (short it = start; it >= end; --it) {
        song += verse(it);
        if (it != end) {
            song += "\n";
        }
    }
    return song;
}