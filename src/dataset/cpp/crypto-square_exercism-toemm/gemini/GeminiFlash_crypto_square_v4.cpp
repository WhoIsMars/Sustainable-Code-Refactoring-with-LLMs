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

  size_t rows = static_cast<size_t>(floor(sqrt(length)));
  size_t cols = static_cast<size_t>(ceil(sqrt(length)));

  if (rows * cols < length) {
    if (cols < rows) {
      cols = rows;
    } else {
      rows = cols;
    }
    if (rows * cols < length) {
      cols++;
    }
  }

  normalized_text.resize(rows * cols, ' ');

  string cipher_text;
  cipher_text.reserve(rows * cols + cols - 1);

  for (size_t col = 0; col < cols; ++col) {
    for (size_t row = 0; row < rows; ++row) {
      cipher_text += normalized_text[col + row * cols];
    }
    if (col < cols - 1) {
      cipher_text += ' ';
    }
  }

  return cipher_text;
}

crypto_square cipher(string msg) { return crypto_square{move(msg)}; }

} // namespace crypto_square