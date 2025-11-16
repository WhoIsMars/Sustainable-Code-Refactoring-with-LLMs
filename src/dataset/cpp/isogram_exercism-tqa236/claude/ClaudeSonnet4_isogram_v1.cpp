#include "isogram.h"

bool isogram::is_isogram(const std::string& phrase) {
  uint32_t letters = 0;
  for (unsigned char c : phrase) {
    if (c >= 'A' && c <= 'Z') {
      c += 32; // Convert to lowercase
    }
    if (c >= 'a' && c <= 'z') {
      int position = c - 'a';
      uint32_t mask = 1u << position;
      if (letters & mask) {
        return false;
      }
      letters |= mask;
    }
  }
  return true;
}