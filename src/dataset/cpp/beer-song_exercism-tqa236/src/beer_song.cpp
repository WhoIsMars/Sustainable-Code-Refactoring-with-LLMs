#include "beer_song.h"

std::string beer_song::verse(int verse_num) {
  if (verse_num == 0) {
    return "No more bottles of beer on the wall, no more bottles of beer.\nGo "
           "to the store and buy some more, 99 bottles of beer on the wall.\n";
  }
  if (verse_num == 1) {
    return std::to_string(verse_num) + " bottle of beer on the wall, " +
           std::to_string(verse_num) +
           " bottle of beer.\nTake it down and pass it around, no more bottles "
           "of beer on the wall.\n";
  }
  if (verse_num == 2) {
    return std::to_string(verse_num) + " bottles of beer on the wall, " +
           std::to_string(verse_num) +
           " bottles of beer.\nTake one down and pass it around, " +
           std::to_string(verse_num - 1) + " bottle of beer on the wall.\n";
  }
  return std::to_string(verse_num) + " bottles of beer on the wall, " +
         std::to_string(verse_num) +
         " bottles of beer.\nTake one down and pass it around, " +
         std::to_string(verse_num - 1) + " bottles of beer on the wall.\n";
}

std::string beer_song::sing(int start, int end) {
  std::string lyrics = "";
  for (int i = start; i > end - 1; --i) {
    lyrics += beer_song::verse(i) + "\n";
  }
  lyrics.pop_back();
  return lyrics;
  ;
}

std::string beer_song::sing(int start) { return beer_song::sing(start, 0); }
