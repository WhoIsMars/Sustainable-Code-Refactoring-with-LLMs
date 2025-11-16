#include "rotational_cipher.h"

#include <algorithm>
#include <cctype>

namespace rotational_cipher {

std::string rotate(std::string in, int shift) {
  if (shift == 0) {
    return in;
  }

  int normalized_shift = shift % 26;
  if (normalized_shift < 0) {
    normalized_shift += 26;
  }

  for (char& ch : in) {
    if (std::isalpha(ch)) {
      char base = std::isupper(ch) ? 'A' : 'a';
      ch = base + (ch - base + normalized_shift) % 26;
    }
  }

  return in;
}

}  // namespace rotational_cipher