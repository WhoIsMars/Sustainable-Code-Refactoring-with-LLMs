#include "crypto_square.h"
#include <algorithm>
#include <cmath>

namespace crypto_square {
cipher::cipher(std::string text) {
  text.erase(std::remove_if(text.begin(), text.end(),
                            [](char c) { return !std::isalnum(c); }),
             text.end());
  std::transform(text.begin(), text.end(), text.begin(), ::tolower);
  column_length = static_cast<int>(ceil(sqrt(text.size())));
  this->text = std::move(text);
  if (column_length * column_length == text.size()) {
    row_length = column_length;
  } else {
    row_length = column_length - 1;
  }
  segmented_text = plain_text_segments();
}
std::string const& cipher::normalize_plain_text() { return text; }
std::vector<std::string> cipher::plain_text_segments() {
  std::vector<std::string> encoded_text;
  for (unsigned int i = 0; i < text.size(); i = i + column_length) {
    encoded_text.push_back(text.substr(i, column_length));
  }
  return encoded_text;
}
std::string cipher::cipher_text() {
  std::string result;
  for (unsigned int i = 0; i < column_length; i++) {
    for (auto chunk : segmented_text) {
      if (i < chunk.size()) {
        result.push_back(chunk[i]);
      }
    }
  }
  return result;
}
std::string cipher::normalized_cipher_text() {
  std::string result;
  for (unsigned int i = 0; i < column_length; i++) {
    if (i > 0) result.push_back(' ');
    for (auto chunk : segmented_text) {
      if (i < chunk.size()) {
        result.push_back(chunk[i]);
      } else {
        result.push_back(' ');
      }
    }
  }
  return result;
}
}  // namespace crypto_square
