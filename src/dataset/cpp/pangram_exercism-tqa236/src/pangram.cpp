#include "pangram.h"

#include <algorithm>
#include <bitset>
#include <stdexcept>
#include <string>

bool pangram::is_pangram(const std::string& sentence) {
  std::bitset<26> letters;
  for (auto c : sentence) {
    try {
      letters.set(tolower(c) - 'a');
    } catch (const std::out_of_range&) {
    }
  }
  return letters.all();
}
