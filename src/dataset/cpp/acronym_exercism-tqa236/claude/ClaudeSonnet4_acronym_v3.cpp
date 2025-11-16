#include "acronym.h"

std::string acronym::acronym(const std::string& name) {
  std::string acronym_name;
  acronym_name.reserve(name.length() / 4);
  
  bool at_word_start = true;
  for (char c : name) {
    if (std::isalpha(static_cast<unsigned char>(c))) {
      if (at_word_start) {
        acronym_name += std::toupper(static_cast<unsigned char>(c));
        at_word_start = false;
      }
    } else {
      at_word_start = true;
    }
  }
  return acronym_name;
}