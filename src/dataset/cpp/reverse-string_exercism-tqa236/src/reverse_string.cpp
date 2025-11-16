#include "reverse_string.h"

std::string reverse_string::reverse_string(std::string s) {
  std::string reverse_s = "";
  for (char c : s) {
    reverse_s = c + reverse_s;
  }
  return reverse_s;
}
