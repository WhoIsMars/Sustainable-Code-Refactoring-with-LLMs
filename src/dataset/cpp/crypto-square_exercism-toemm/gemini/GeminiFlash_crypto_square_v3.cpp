#include "crypto_square.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>

namespace crypto_square {

using namespace std;

crypto_square::crypto_square(string msg) : _msg(move(msg)) {}

string crypto_square::normalized_cipher_text() {
  string normalized_text;
  normalized_text.reserve(_msg.length());

  for (char ch : _msg) {
    if (isalnum(ch)) {
      normalized_text += tolower(ch);
    }
  }

  size_t length = normalized_text.length();
  if (length == 0) {
    return "";
  }

  int c = ceil(sqrt(length));
  int r = (length + c - 1) / c;

  string cipher_text;
  cipher_text.reserve(c * (r + 1)); 

  for (int j = 0; j < c; ++j) {
    for (int k = 0; k < r; ++k) {
      size_t index = j + k * c;
      if (index < length) {
        cipher_text += normalized_text[index];
      } else {
        cipher_text += ' ';
      }
    }
    cipher_text += ' ';
  }

  cipher_text.pop_back();

  return cipher_text;
}

crypto_square cipher(string msg) { return crypto_square{move(msg)}; }

}  // namespace crypto_square