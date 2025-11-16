#include "reverse_string.h"

std::string reverse_string::reverse_string(std::string s) {
  if (s.empty()) return s;
  
  std::reverse(s.begin(), s.end());
  return s;
}