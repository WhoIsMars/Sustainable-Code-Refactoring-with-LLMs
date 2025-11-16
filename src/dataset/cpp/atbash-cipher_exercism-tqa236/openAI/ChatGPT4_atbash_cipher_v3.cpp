#include "atbash_cipher.h"
#include <cctype>

std::string atbash_cipher::transform(const std::string& text, bool add_space) {
  std::string cipher;
  cipher.reserve(text.size());
  int count = 0;

  for (char c : text) {
    if (std::isalpha(c)) {
      if (add_space && count > 0 && count % 5 == 0) {
        cipher += ' ';
      }
      cipher += static_cast<char>('a' + 'z' - std::tolower(c));
      ++count;
    } else if (std::isdigit(c)) {
      if (add_space && count > 0 && count % 5 == 0) {
        cipher += ' ';
      }
      cipher += c;
      ++count;
    }
  }

  return cipher;
}

std::string atbash_cipher::encode(const std::string& text) {
  return transform(text, true);
}

std::string atbash_cipher::decode(const std::string& text) {
  return transform(text, false);
}