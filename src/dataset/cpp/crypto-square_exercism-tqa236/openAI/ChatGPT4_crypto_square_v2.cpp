#include "crypto_square.h"
#include <algorithm>
#include <cmath>
#include <sstream>

namespace crypto_square {

cipher::cipher(std::string text) {
  text.erase(std::remove_if(text.begin(), text.end(),
                            [](unsigned char c) { return !std::isalnum(c); }),
             text.end());
  std::transform(text.begin(), text.end(), text.begin(), ::tolower);
  column_length = static_cast<int>(std::ceil(std::sqrt(text.size())));
  this->text = std::move(text);
  row_length = (column_length * column_length == this->text.size()) ? column_length : column_length - 1;
}

std::string const& cipher::normalize_plain_text() { 
  return text; 
}

std::vector<std::string> cipher::plain_text_segments() {
  if (!segmented_text.empty()) return segmented_text;
  segmented_text.reserve((text.size() + column_length - 1) / column_length);
  for (size_t i = 0; i < text.size(); i += column_length) {
    segmented_text.emplace_back(text.substr(i, column_length));
  }
  return segmented_text;
}

std::string cipher::cipher_text() {
  if (segmented_text.empty()) plain_text_segments();
  std::ostringstream result;
  for (size_t i = 0; i < column_length; ++i) {
    for (const auto& chunk : segmented_text) {
      if (i < chunk.size()) {
        result.put(chunk[i]);
      }
    }
  }
  return result.str();
}

std::string cipher::normalized_cipher_text() {
  if (segmented_text.empty()) plain_text_segments();
  std::ostringstream result;
  for (size_t i = 0; i < column_length; ++i) {
    if (i > 0) result.put(' ');
    for (const auto& chunk : segmented_text) {
      result.put(i < chunk.size() ? chunk[i] : ' ');
    }
  }
  return result.str();
}

}  // namespace crypto_square