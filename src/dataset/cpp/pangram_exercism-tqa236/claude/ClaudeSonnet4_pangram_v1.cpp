#include "pangram.h"

#include <string>

bool pangram::is_pangram(const std::string& sentence) {
  unsigned int letters = 0;
  for (char c : sentence) {
    if (c >= 'a' && c <= 'z') {
      letters |= 1u << (c - 'a');
    } else if (c >= 'A' && c <= 'Z') {
      letters |= 1u << (c - 'A');
    }
    if (letters == 0x3FFFFFF) return true;
  }
  return letters == 0x3FFFFFF;
}