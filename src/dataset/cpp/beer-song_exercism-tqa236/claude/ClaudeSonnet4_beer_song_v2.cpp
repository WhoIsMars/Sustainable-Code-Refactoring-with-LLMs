#include "beer_song.h"

std::string beer_song::verse(int verse_num) {
  switch (verse_num) {
    case 0:
      return "No more bottles of beer on the wall, no more bottles of beer.\nGo "
             "to the store and buy some more, 99 bottles of beer on the wall.\n";
    case 1:
      return "1 bottle of beer on the wall, 1 bottle of beer.\nTake it down and pass it around, no more bottles of beer on the wall.\n";
    case 2:
      return "2 bottles of beer on the wall, 2 bottles of beer.\nTake one down and pass it around, 1 bottle of beer on the wall.\n";
    default: {
      const std::string num_str = std::to_string(verse_num);
      const std::string prev_num_str = std::to_string(verse_num - 1);
      return num_str + " bottles of beer on the wall, " + num_str +
             " bottles of beer.\nTake one down and pass it around, " +
             prev_num_str + " bottles of beer on the wall.\n";
    }
  }
}

std::string beer_song::sing(int start, int end) {
  std::string lyrics;
  lyrics.reserve((start - end + 1) * 150); // Pre-allocate approximate memory
  
  for (int i = start; i >= end; --i) {
    lyrics += beer_song::verse(i);
    if (i > end) {
      lyrics += '\n';
    }
  }
  return lyrics;
}

std::string beer_song::sing(int start) { 
  return beer_song::sing(start, 0); 
}