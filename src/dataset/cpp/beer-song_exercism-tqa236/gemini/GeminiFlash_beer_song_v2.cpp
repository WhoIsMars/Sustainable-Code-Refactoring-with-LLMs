#include "beer_song.h"

#include <sstream>

std::string beer_song::verse(int verse_num) {
  if (verse_num == 0) {
    return "No more bottles of beer on the wall, no more bottles of beer.\nGo "
           "to the store and buy some more, 99 bottles of beer on the wall.\n";
  }

  std::stringstream ss;
  if (verse_num == 1) {
    ss << verse_num << " bottle of beer on the wall, " << verse_num
       << " bottle of beer.\nTake it down and pass it around, no more bottles "
          "of beer on the wall.\n";
  } else {
    ss << verse_num << " bottles of beer on the wall, " << verse_num
       << " bottles of beer.\nTake one down and pass it around, "
       << verse_num - 1 << (verse_num == 2 ? " bottle" : " bottles")
       << " of beer on the wall.\n";
  }
  return ss.str();
}

std::string beer_song::sing(int start, int end) {
  std::stringstream lyrics;
  for (int i = start; i > end - 1; --i) {
    lyrics << beer_song::verse(i);
    if (i != end) {
      lyrics << "\n";
    }
  }
  return lyrics.str();
}

std::string beer_song::sing(int start) { return beer_song::sing(start, 0); }