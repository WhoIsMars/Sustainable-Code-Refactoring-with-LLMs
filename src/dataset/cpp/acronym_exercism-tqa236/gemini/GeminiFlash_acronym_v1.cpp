#include "acronym.h"
#include <algorithm>
#include <cctype>

std::string acronym::acronym(const std::string& name) {
  std::string acronym_name;
  acronym_name.reserve(name.length() / 2); // Pre-allocate memory

  bool new_word = true;
  for (char c : name) {
    if (std::isalpha(c)) {
      if (new_word) {
        acronym_name += std::toupper(static_cast<unsigned char>(c)); // Avoid potential issues with signed chars
        new_word = false;
      }
    } else {
      new_word = true;
    }
  }
  return acronym_name;
}