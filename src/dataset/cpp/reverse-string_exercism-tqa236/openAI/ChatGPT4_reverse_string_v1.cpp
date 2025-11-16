#include "reverse_string.h"

std::string reverse_string::reverse_string(std::string s) {
  std::reverse(s.begin(), s.end());
  return s;
}