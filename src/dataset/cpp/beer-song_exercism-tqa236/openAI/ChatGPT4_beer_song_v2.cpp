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
    default:
      return std::to_string(verse_num) + " bottles of beer on the wall, " +
             std::to_string(verse_num) +
             " bottles of beer.\nTake one down and pass it around, " +
             std::to_string(verse_num - 1) + " bottles of beer on the wall.\n";
  }
}

std::string beer_song::sing(int start, int end) {
  std::string lyrics;
  for (int i = start; i >= end; --i) {
    if (!lyrics.empty()) lyrics += "\n";
    lyrics += beer_song::verse(i);
  }
  return lyrics;
}

std::string beer_song::sing(int start) {
  return beer_song::sing(start, 0);
}