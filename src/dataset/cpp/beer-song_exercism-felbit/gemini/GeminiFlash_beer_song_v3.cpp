#include "beer_song.h"
#include <sstream>

std::string beer::verse(const short bottles) {
    std::stringstream ss;
    switch (bottles) {
        case 0:
            ss << "No more bottles of beer on the wall, no more bottles of beer.\n"
               << "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
            break;
        case 1:
            ss << "1 bottle of beer on the wall, 1 bottle of beer.\n"
               << "Take it down and pass it around, no more bottles of beer on the wall.\n";
            break;
        case 2:
            ss << "2 bottles of beer on the wall, 2 bottles of beer.\n"
               << "Take one down and pass it around, 1 bottle of beer on the wall.\n";
            break;
        default:
            ss << bottles << " bottles of beer on the wall, " << bottles << " bottles of beer.\n"
               << "Take one down and pass it around, " << (bottles - 1) << " bottles of beer on the wall.\n";
            break;
    }
    return ss.str();
}

std::string beer::sing(const short start, const short end) {
    std::stringstream song;
    for (short it = start; it >= end; --it) {
        song << verse(it);
        if (it != end) {
            song << "\n";
        }
    }
    return song.str();
}