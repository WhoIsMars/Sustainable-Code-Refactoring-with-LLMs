#include "atbash_cipher.h"
#include <algorithm>
#include <cctype>

std::string atbash_cipher::transform(const std::string& text, bool add_space) {
  std::string cipher;
  cipher.reserve(text.length()); // Pre-allocate memory to avoid reallocations

  int count = 0;
  for (char c : text) {
    if (!std::isalnum(c)) continue;

    if (add_space && (count % 5 == 0) && (count > 0)) {
      cipher += ' ';
    }

    if (std::isdigit(c)) {
      cipher += c;
    } else {
      cipher += (char)('a' + 'z' - std::tolower(c));
    }
    count++;
  }
  return cipher;
}

std::string atbash_cipher::encode(const std::string& text) {
  std::string encoded = transform(text, true);
  return encoded;
}

std::string atbash_cipher::decode(const std::string& text) {
  return transform(text, false);
}