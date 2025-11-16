#include "beer_song.h"
#include <string>

std::string beer_song::verse(int n) noexcept {
    switch (n) {
        case 0:
            return  "No more bottles of beer on the wall, " 
                    "no more bottles of beer.\nGo "
                    "to the store and buy some more, "
                    "99 bottles of beer on the wall.\n";
        case 1:
            return  "1 bottle of beer on the wall, "
                    "1 bottle of beer.\nTake it down and "
                    "pass it around, no more bottles "
                    "of beer on the wall.\n";
        case 2: 
            return  "2 bottles of beer on the wall, "
                    "2 bottles of beer.\nTake one down "
                    "and pass it around, 1 bottle "
                    "of beer on the wall.\n";
        default: {
            const std::string n_str = std::to_string(n);
            const std::string n_minus_1_str = std::to_string(n - 1);
            
            std::string result;
            result.reserve(120);
            result += n_str;
            result += " bottles of beer on the wall, ";
            result += n_str;
            result += " bottles of beer.\nTake one down and pass it around, ";
            result += n_minus_1_str;
            result += " bottles of beer on the wall.\n";
            return result;
        }
    }
}

std::string beer_song::sing(int start, int end) noexcept {
    std::string verses;
    verses.reserve((start - end + 1) * 120);
    
    for( int n = start; n >= end; --n ) {
        if( n != start ) verses += '\n';
        verses += verse(n);
    }
    return verses;
}

std::string beer_song::sing(int start) noexcept {
    return sing(start, 0);
}