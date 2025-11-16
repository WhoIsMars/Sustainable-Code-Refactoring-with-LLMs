#include "acronym.h"

std::string acronym::acronym(const std::string& name) {
  std::string acronym_name;
  acronym_name.reserve(name.length() / 4); // Estimate capacity to reduce reallocations
  
  bool flag = true;
  for (char c : name) {
    if (flag && std::isalpha(static_cast<unsigned char>(c))) {
      acronym_name += std::toupper(static_cast<unsigned char>(c));
      flag = false;
    } else if (!std::isalpha(static_cast<unsigned char>(c))) {
      flag = true;
    }
  }
  return acronym_name;
}