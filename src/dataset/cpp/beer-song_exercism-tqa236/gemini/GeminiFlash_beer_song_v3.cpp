#include "beer_song.h"
#include <sstream>

std::string beer_song::verse(int verse_num) {
  std::ostringstream verse_stream;

  if (verse_num == 0) {
    verse_stream << "No more bottles of beer on the wall, no more bottles of beer.\n"
                  << "Go to the store and buy some more, 99 bottles of beer on the wall.\n";
  } else if (verse_num == 1) {
    verse_stream << verse_num << " bottle of beer on the wall, "
                  << verse_num << " bottle of beer.\n"
                  << "Take it down and pass it around, no more bottles of beer on the wall.\n";
  } else {
    verse_stream << verse_num << " bottles of beer on the wall, "
                  << verse_num << " bottles of beer.\n"
                  << "Take one down and pass it around, "
                  << verse_num - 1 << (verse_num == 2 ? " bottle" : " bottles") << " of beer on the wall.\n";
  }

  return verse_stream.str();
}

std::string beer_song::sing(int start, int end) {
  std::string lyrics;
  lyrics.reserve((start - end + 1) * 200);

  for (int i = start; i >= end; --i) {
    lyrics += verse(i);
    if (i != end) {
      lyrics += "\n";
    }
  }

  return lyrics;
}

std::string beer_song::sing(int start) { return sing(start, 0); }