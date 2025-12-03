#include "food_chain.h"
#include <array>
#include <string>

namespace {
constexpr std::array<std::pair<const char*, const char*>, 9> song_info = {
    {{nullptr, nullptr},
     {"fly", "I don't know why she swallowed the fly. Perhaps she'll die."},
     {"spider", "It wriggled and jiggled and tickled inside her."},
     {"bird", "How absurd to swallow a bird!"},
     {"cat", "Imagine that, to swallow a cat!"},
     {"dog", "What a hog, to swallow a dog!"},
     {"goat", "Just opened her throat and swallowed a goat!"},
     {"cow", "I don't know how she swallowed a cow!"},
     {"horse", "She's dead, of course!"}}};

constexpr const char* const fly_reaction =
    "I don't know why she swallowed the fly. Perhaps she'll die.\n";
} // namespace

std::string food_chain::verse(int num) {
  std::string res;
  res.reserve(256); // Pre-allocate memory to avoid reallocations

  res += "I know an old lady who swallowed a ";
  res += song_info[num].first;
  res += ".\n";

  if (num > FLY) {
    res += song_info[num].second;
    res += "\n";
  }

  if (num == HORSE) {
    return res;
  }

  int current = num;
  while (current > FLY) {
    res += "She swallowed the ";
    res += song_info[current].first;
    res += " to catch the ";
    res += song_info[current - 1].first;

    if (--current == SPIDER) {
      res += " that wriggled and jiggled and tickled inside her.\n";
    } else {
      res += ".\n";
    }
  }

  res += fly_reaction;
  return res;
}

std::string food_chain::verses(int start, int end) {
  std::string res;
  res.reserve((end - start + 1) * 256); // Pre-allocate memory

  for (int i = start; i <= end; ++i) {
    res += verse(i);
    res += "\n";
  }
  return res;
}

std::string food_chain::sing() { return verses(1, 8); }