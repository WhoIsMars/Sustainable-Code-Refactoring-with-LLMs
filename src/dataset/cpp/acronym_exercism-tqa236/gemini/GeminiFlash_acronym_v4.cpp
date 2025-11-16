#include "acronym.h"
#include <algorithm>
#include <cctype>

std::string acronym::acronym(const std::string& name) {
  std::string acronym_name;
  acronym_name.reserve(name.length() / 2); // Pre-allocate memory

  bool need_upper = true;
  for (char c : name) {
    if (std::isalpha(static_cast<unsigned char>(c))) {
      if (need_upper) {
        acronym_name += std::toupper(static_cast<unsigned char>(c));
        need_upper = false;
      }
    } else {
      need_upper = true;
    }
  }
  return acronym_name;
}