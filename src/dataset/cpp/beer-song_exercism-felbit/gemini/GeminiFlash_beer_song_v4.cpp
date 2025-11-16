#include "beer_song.h"
#include <array>

std::string beer::verse(const short bottles) {
    switch (bottles) {
        case 0:
            return "No more bottles of beer on the wall, no more bottles of beer.\n"
                   "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
        case 1:
            return "1 bottle of beer on the wall, 1 bottle of beer.\n"
                   "Take it down and pass it around, no more bottles of beer on the wall.\n";
        case 2:
            return "2 bottles of beer on the wall, 2 bottles of beer.\n"
                   "Take one down and pass it around, 1 bottle of beer on the wall.\n";
        default: {
            std::string verse_string;
            verse_string.reserve(150); 

            verse_string += std::to_string(bottles);
            verse_string += " bottles of beer on the wall, ";
            verse_string += std::to_string(bottles);
            verse_string += " bottles of beer.\nTake one down and pass it around, ";
            verse_string += std::to_string(bottles - 1);
            verse_string += " bottles of beer on the wall.\n";
            return verse_string;
        }
    }
}

std::string beer::sing(const short start, const short end) {
    std::string song;
    for (short i = start; i >= end; --i) {
        song += verse(i);
        if (i != end) {
            song += "\n";
        }
    }
    return song;
}