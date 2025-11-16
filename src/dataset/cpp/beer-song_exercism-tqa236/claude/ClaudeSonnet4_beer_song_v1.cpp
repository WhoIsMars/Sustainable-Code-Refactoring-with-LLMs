#include "beer_song.h"

std::string beer_song::verse(int verse_num) {
  if (verse_num == 0) {
    return "No more bottles of beer on the wall, no more bottles of beer.\nGo "
           "to the store and buy some more, 99 bottles of beer on the wall.\n";
  }
  
  const std::string num_str = std::to_string(verse_num);
  const char* bottle_word = (verse_num == 1) ? " bottle" : " bottles";
  
  if (verse_num == 1) {
    return num_str + bottle_word + " of beer on the wall, " + num_str +
           bottle_word + " of beer.\nTake it down and pass it around, no more bottles "
           "of beer on the wall.\n";
  }
  
  const std::string next_num_str = std::to_string(verse_num - 1);
  const char* next_bottle_word = (verse_num == 2) ? " bottle" : " bottles";
  
  return num_str + bottle_word + " of beer on the wall, " + num_str +
         bottle_word + " of beer.\nTake one down and pass it around, " +
         next_num_str + next_bottle_word + " of beer on the wall.\n";
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