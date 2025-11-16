#include "pangram.h"

#include <bitset>
#include <string>
#include <cctype>

bool pangram::is_pangram(const std::string& sentence) {
  std::bitset<26> letters;
  for (char c : sentence) {
    if (std::isalpha(c)) {
      letters.set(std::tolower(c) - 'a');
      if (letters.all()) return true;
    }
  }
  return false;
}