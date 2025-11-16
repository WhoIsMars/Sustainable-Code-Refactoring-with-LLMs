#include "pangram.h"

#include <bitset>
#include <string>

bool pangram::is_pangram(const std::string& sentence) {
  std::bitset<26> letters;
  for (char c : sentence) {
    if (c >= 'a' && c <= 'z') {
      letters.set(c - 'a');
    } else if (c >= 'A' && c <= 'Z') {
      letters.set(c - 'A');
    }
    if (letters.all()) {
      return true;
    }
  }
  return letters.all();
}