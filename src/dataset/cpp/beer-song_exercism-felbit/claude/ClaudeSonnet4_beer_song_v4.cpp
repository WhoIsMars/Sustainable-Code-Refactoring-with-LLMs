#include "beer_song.h"

std::string beer::verse(const short bottles)
{
    static const std::string zero_verse = 
        "No more bottles of beer on the wall, no more bottles of beer.\n"
        "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
    
    static const std::string one_verse = 
        "1 bottle of beer on the wall, 1 bottle of beer.\n"
        "Take it down and pass it around, no more bottles of beer on the wall.\n";
    
    static const std::string two_verse = 
        "2 bottles of beer on the wall, 2 bottles of beer.\n"
        "Take one down and pass it around, 1 bottle of beer on the wall.\n";

    switch (bottles)
    {
    case 0:
        return zero_verse;
    case 1:
        return one_verse;
    case 2:
        return two_verse;
    default:
        {
            const std::string bottles_str = std::to_string(bottles);
            const std::string bottles_minus_one = std::to_string(bottles - 1);
            
            std::string result;
            result.reserve(120);
            result += bottles_str;
            result += " bottles of beer on the wall, ";
            result += bottles_str;
            result += " bottles of beer.\nTake one down and pass it around, ";
            result += bottles_minus_one;
            result += " bottles of beer on the wall.\n";
            return result;
        }
    }
}

std::string beer::sing(const short start, const short end)
{
    const size_t verse_count = start - end + 1;
    std::string song;
    song.reserve(verse_count * 120);
    
    for (short it = start; it >= end; --it)
    {
        song += verse(it);
        if (it != end) song += '\n';
    }
    return song;
}