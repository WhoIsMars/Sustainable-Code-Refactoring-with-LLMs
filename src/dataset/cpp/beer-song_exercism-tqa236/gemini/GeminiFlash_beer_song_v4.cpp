#include "beer_song.h"

#include <sstream>

std::string beer_song::verse(int verse_num) {
  std::ostringstream oss;
  if (verse_num == 0) {
    oss << "No more bottles of beer on the wall, no more bottles of beer.\n"
        << "Go to the store and buy some more, 99 bottles of beer on the "
           "wall.\n";
  } else if (verse_num == 1) {
    oss << verse_num << " bottle of beer on the wall, " << verse_num
        << " bottle of beer.\n"
        << "Take it down and pass it around, no more bottles of beer on the "
           "wall.\n";
  } else {
    oss << verse_num << " bottles of beer on the wall, " << verse_num
        << " bottles of beer.\n"
        << "Take one down and pass it around, " << verse_num - 1
        << (verse_num == 2 ? " bottle" : " bottles") << " of beer on the "
        << "wall.\n";
  }
  return oss.str();
}

std::string beer_song::sing(int start, int end) {
  std::string lyrics;
  for (int i = start; i >= end; --i) {
    lyrics += beer_song::verse(i);
    if (i != end) {
      lyrics += "\n";
    }
  }
  return lyrics;
}

std::string beer_song::sing(int start) { return beer_song::sing(start, 0); }