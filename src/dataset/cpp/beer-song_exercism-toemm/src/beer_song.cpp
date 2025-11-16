#include "beer_song.h"

#include <sstream>
#include <iostream>

namespace beer_song {

std::string verse(int i) {

    std::ostringstream out;

    if (i == 0) {
        out << "No more bottles of beer on the wall, no more bottles of beer.\n" <<
        "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
        return out.str();
    }

    out << i << ((i == 1) ? " bottle" : " bottles") << " of beer on the wall, " << i 
                            << ((i == 1) ? " bottle" : " bottles") << " of beer.\n"
                            << "Take " << ((i == 1) ? "it" : "one") << " down and pass it around, " 
                            << ((i == 1) ? "no more" : std::to_string(i-1)) + " bottle" 
                            << ((i == 2) ? "" : "s") << " of beer on the wall.\n";

    //std::cout << out.str();
    return out.str();

}


std::string sing(int begin, int ending) {

    std::string out;

    for (int i{begin}; i >= ending; i--)
        out = out + verse(i) + ((i != ending) ? "\n" : "");

    return out;

}

}  // namespace beer_song
