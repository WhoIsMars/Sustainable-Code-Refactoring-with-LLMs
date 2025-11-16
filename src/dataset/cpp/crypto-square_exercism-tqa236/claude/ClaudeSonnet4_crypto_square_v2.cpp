#include "crypto_square.h"
#include <algorithm>
#include <cmath>

namespace crypto_square {
cipher::cipher(std::string text) {
  // Remove non-alphanumeric and convert to lowercase in single pass
  auto write_it = text.begin();
  for (auto read_it = text.begin(); read_it != text.end(); ++read_it) {
    if (std::isalnum(*read_it)) {
      *write_it = std::tolower(*read_it);
      ++write_it;
    }
  }
  text.erase(write_it, text.end());
  
  column_length = static_cast<int>(ceil(sqrt(text.size())));
  this->text = std::move(text);
  
  // Simplified row_length calculation
  row_length = (column_length * column_length == this->text.size()) ? 
               column_length : column_length - 1;
  
  segmented_text = plain_text_segments();
}

std::string const& cipher::normalize_plain_text() { return text; }

std::vector<std::string> cipher::plain_text_segments() {
  std::vector<std::string> encoded_text;
  encoded_text.reserve((text.size() + column_length - 1) / column_length);
  
  for (size_t i = 0; i < text.size(); i += column_length) {
    encoded_text.emplace_back(text, i, column_length);
  }
  return encoded_text;
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