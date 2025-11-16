#include "atbash_cipher.h"
#include <algorithm>

std::string atbash_cipher::transform(const std::string& text, bool add_space) {
  std::string cipher;
  int count = 0;
  for (char c : text) {
    if (::ispunct(c) || c == ' ') continue;
    if (add_space && (count % 5 == 0) && (count > 0)) {
      cipher += ' ';
    }
    if (isdigit(c)) {
      cipher += c;
    } else {
      cipher += (char)('a' + 'z' - tolower(c));
    }
    count += 1;
  }
  return cipher;
}

std::string atbash_cipher::encode(const std::string& text) {
  return transform(text, true);
}

std::string atbash_cipher::decode(const std::string& text) {
  return transform(text, false);
}
