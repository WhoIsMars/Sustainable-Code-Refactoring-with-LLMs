#include "isogram.h"

bool isogram::is_isogram(const std::string& phrase) {
  uint32_t letters = 0;
  for (char c : phrase) {
    if (c >= 'A' && c <= 'Z') {
      c |= 0x20;
    }
    if (c >= 'a' && c <= 'z') {
      const uint32_t bit = 1u << (c - 'a');
      if (letters & bit) {
        return false;
      }
      letters |= bit;
    }
  }
  return true;
}