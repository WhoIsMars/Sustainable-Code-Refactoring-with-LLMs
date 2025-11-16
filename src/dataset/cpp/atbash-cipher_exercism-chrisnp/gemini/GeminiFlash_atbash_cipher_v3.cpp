#include "atbash_cipher.h"
#include "test/catch.hpp"
#include <algorithm>
#include <cctype>

namespace {
constexpr bool is_alphanumeric(char c) noexcept {
  return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z');
}
} // namespace

std::string atbash_cipher::encode(const std::string &plain) noexcept {
  std::string ciphertext;
  ciphertext.reserve(plain.size() * 6 / 5); // Pre-allocate memory

  int index = 0;
  for (char ch : plain) {
    char c = tolower(ch);
    if (!is_alphanumeric(c))
      continue;

    if (index > 0 && index % 5 == 0) {
      ciphertext.push_back(' ');
    }

    if (isdigit(c)) {
      ciphertext.push_back(c);
    } else {
      ciphertext.push_back('z' - c + 'a');
    }
    ++index;
  }
  return ciphertext;
}

std::string atbash_cipher::decode(const std::string &cipher) {
  std::string plaintext;
  plaintext.reserve(cipher.size());

  for (char c : cipher) {
    if (c == ' ')
      continue;

    if (isdigit(c)) {
      plaintext.push_back(c);
    } else if (isalpha(c)) {
      plaintext.push_back('a' - c + 'z');
    } else {
      Catch::throw_domain_error("Bad cipher");
    }
  }
  return plaintext;
}