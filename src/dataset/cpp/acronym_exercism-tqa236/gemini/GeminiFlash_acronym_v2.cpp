#include "acronym.h"
#include <algorithm>
#include <cctype>

std::string acronym::acronym(const std::string& name) {
  std::string acronym_name;
  acronym_name.reserve(name.length() / 2); // Pre-allocate memory

  bool need_acronym = true;
  for (char c : name) {
    if (std::isalpha(c)) {
      if (need_acronym) {
        acronym_name += std::toupper(static_cast<unsigned char>(c)); // Avoid potential issues with signed chars
        need_acronym = false;
      }
    } else {
      need_acronym = true;
    }
  }
  return acronym_name;
}