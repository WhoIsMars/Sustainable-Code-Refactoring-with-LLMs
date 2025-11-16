#include "acronym.h"

std::string acronym::acronym(const std::string& name) {
  std::string acronym_name = "";
  bool flag = true;
  for (unsigned char c : name) {
    if (std::isalpha(c)) {
      if (flag) {
        acronym_name += std::toupper(c);
        flag = false;
      }
    } else {
      flag = true;
    }
  }
  return acronym_name;
}
