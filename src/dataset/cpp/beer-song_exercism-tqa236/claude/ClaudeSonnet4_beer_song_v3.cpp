#include "beer_song.h"

std::string beer_song::verse(int verse_num) {
    switch (verse_num) {
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
            const std::string num_str = std::to_string(verse_num);
            const std::string next_num_str = std::to_string(verse_num - 1);
            std::string result;
            result.reserve(120);
            result += num_str;
            result += " bottles of beer on the wall, ";
            result += num_str;
            result += " bottles of beer.\nTake one down and pass it around, ";
            result += next_num_str;
            result += " bottles of beer on the wall.\n";
            return result;
        }
    }
}

std::string beer_song::sing(int start, int end) {
    std::string lyrics;
    lyrics.reserve((start - end + 1) * 120);
    
    for (int i = start; i >= end; --i) {
        lyrics += verse(i);
        if (i > end) {
            lyrics += '\n';
        }
    }
    
    return lyrics;
}

std::string beer_song::sing(int start) {
    return sing(start, 0);
}