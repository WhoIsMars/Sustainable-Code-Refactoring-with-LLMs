#include "crypto_square.h"
#include <algorithm>
#include <cmath>

namespace crypto_square {
cipher::cipher(std::string text) {
  text.erase(std::remove_if(text.begin(), text.end(),
                            [](char c) { return !std::isalnum(c); }),
             text.end());
  std::transform(text.begin(), text.end(), text.begin(), ::tolower);
  
  const size_t text_size = text.size();
  column_length = static_cast<int>(ceil(sqrt(text_size)));
  this->text = std::move(text);
  
  if (column_length * column_length == text_size) {
    row_length = column_length;
  } else {
    row_length = column_length - 1;
  }
  
  segmented_text.reserve((text_size + column_length - 1) / column_length);
  for (size_t i = 0; i < text_size; i += column_length) {
    segmented_text.emplace_back(this->text.substr(i, column_length));
  }
}

std::string const& cipher::normalize_plain_text() { 
  return text; 
}

std::vector<std::string> cipher::plain_text_segments() {
  return segmented_text;
}

std::string cipher::cipher_text() {
  std::string result;
  result.reserve(text.size());
  
  for (int i = 0; i < column_length; ++i) {
    for (const auto& chunk : segmented_text) {
      if (i < static_cast<int>(chunk.size())) {
        result.push_back(chunk[i]);
      }
    }
  }
  return result;
}

std::string cipher::normalized_cipher_text() {
  std::string result;
  result.reserve(text.size() + column_length - 1);
  
  for (int i = 0; i < column_length; ++i) {
    if (i > 0) result.push_back(' ');
    for (const auto& chunk : segmented_text) {
      if (i < static_cast<int>(chunk.size())) {
        result.push_back(chunk[i]);
      } else {
        result.push_back(' ');
      }
    }
  }
  return result;
}
}  // namespace crypto_square