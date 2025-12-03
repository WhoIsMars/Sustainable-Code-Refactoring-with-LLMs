#include "food_chain.h"
#include <array>
#include <string>

namespace food_chain {

const std::array<VERSE_INFO, 9> song_info = {{
    {},
    {"fly", "I don't know why she swallowed the fly. Perhaps she'll die."},
    {"spider", "It wriggled and jiggled and tickled inside her."},
    {"bird", "How absurd to swallow a bird!"},
    {"cat", "Imagine that, to swallow a cat!"},
    {"dog", "What a hog, to swallow a dog!"},
    {"goat", "Just opened her throat and swallowed a goat!"},
    {"cow", "I don't know how she swallowed a cow!"},
    {"horse", "She's dead, of course!"},
}};

std::string verse(int num) {
  std::string res;
  res.reserve(256); 

  res += "I know an old lady who swallowed a ";
  res += song_info[num].animal;
  res += ".\n";

  if (num > FLY) {
    res += song_info[num].reaction;
    res += "\n";
  }

  if (num == HORSE) return res;

  int current = num;
  while (current > FLY) {
    res += "She swallowed the ";
    res += song_info[current].animal;
    res += " to catch the ";
    res += song_info[current - 1].animal;

    if (--current == SPIDER) {
      res += " that wriggled and jiggled and tickled inside her.\n";
    } else {
      res += ".\n";
    }
  }

  res += song_info[FLY].reaction;
  res += "\n";
  return res;
}

std::string verses(int start, int end) {
  std::string res;
  res.reserve((end - start + 1) * 256);

  for (int i = start; i <= end; ++i) {
    res += verse(i);
    res += "\n";
  }
  return res;
}

std::string sing() { return verses(1, 8); }

}  // namespace food_chain