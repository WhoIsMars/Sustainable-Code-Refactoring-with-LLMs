#include "food_chain.h"
#include <array>
#include <string>

namespace {
constexpr std::array<VERSE_INFO, 9> song_info = {{
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

std::string build_verse(int num) {
  std::string res =
      "I know an old lady who swallowed a " + song_info[num].animal + ".\n";

  if (num > 1) {
    res += (song_info[num].reaction + "\n");
  }

  if (num == 8) return res;

  for (int i = num; i > 1; --i) {
    res += ("She swallowed the " + song_info[i].animal + " to catch the " +
            song_info[i - 1].animal);
    if (i - 1 == 2) {
      res += " that wriggled and jiggled and tickled inside her.\n";
    } else {
      res += ".\n";
    }
  }

  return res += (song_info[1].reaction + "\n");
}
} // namespace

std::string food_chain::verse(int num) { return build_verse(num); }

std::string food_chain::verses(int start, int end) {
  std::string res;
  for (int i = start; i <= end; ++i) {
    res += build_verse(i);
    if (i < end) {
      res += "\n";
    }
  }
  return res;
}

std::string food_chain::sing() { return verses(1, 8); }