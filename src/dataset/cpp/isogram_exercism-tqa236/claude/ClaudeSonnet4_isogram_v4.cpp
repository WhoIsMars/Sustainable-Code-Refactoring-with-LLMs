#include "isogram.h"
#include <cstdint>

bool isogram::is_isogram(const std::string& phrase) {
  std::uint32_t letters = 0;
  for (unsigned char c : phrase) {
    if (c >= 'A' && c <= 'Z') {
      c += 32;
    }
    if (c >= 'a' && c <= 'z') {
      const std::uint32_t bit = 1U << (c - 'a');
      if (letters & bit) {
        return false;
      }
      letters |= bit;
    }
  }
  return true;
}