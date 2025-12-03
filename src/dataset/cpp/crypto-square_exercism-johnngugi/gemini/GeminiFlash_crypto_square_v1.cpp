#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>

namespace crypto_square {

cipher::cipher(std::string text) : initial(std::move(text)) {}

std::string cipher::normalize_plain_text() {
  std::string result;
  result.reserve(initial.length()); // Reserve space to avoid reallocations

  for (char c : initial) {
    if (isalnum(c)) {
      result += static_cast<char>(tolower(c));
    }
  }

  return normalized_text = result; // Store normalized text
}

unsigned int cipher::calculate_size(const std::string& text) {
  size_t text_length = text.length();
  return static_cast<unsigned int>(ceil(sqrt(text_length)));
}

unsigned int cipher::size() {
  if (normalized_text.empty()) {
    normalize_plain_text(); // Ensure normalized text is calculated
  }
  return calculate_size(normalized_text);
}

const std::vector<std::string> cipher::create_segments(const std::string& text) {
  unsigned int size = calculate_size(text);
  std::vector<std::string> segments;
  segments.reserve((text.length() + size - 1) / size); // Reserve space

  for (unsigned int i = 0; i < text.length(); i += size) {
    segments.emplace_back(text.substr(i, size));
  }

  return segments;
}

const std::vector<std::string> cipher::plain_text_segments() {
  if (normalized_text.empty()) {
    normalize_plain_text(); // Ensure normalized text is calculated
  }
  return create_segments(normalized_text);
}

std::string cipher::cipher_text() {
  const std::vector<std::string>& segments = plain_text_segments();
  if (segments.empty()) return "";

  unsigned int rows = segments.size();
  unsigned int columns = segments[0].length();

  std::string result;
  result.reserve(rows * columns);

  for (unsigned int column = 0; column < columns; ++column) {
    for (unsigned int row = 0; row < rows; ++row) {
      if (column < segments[row].length()) {
        result += segments[row][column];
      }
    }
  }

  return result;
}

std::string cipher::normalized_cipher_text() {
  std::string ciphertext_val = cipher_text();
  const std::vector<std::string> segments = create_segments(ciphertext_val);

  std::string result;
  if (!segments.empty()) {
    result = segments[0];
    for (size_t i = 1; i < segments.size(); ++i) {
      result += " " + segments[i];
    }
  }
  return result;
}

} // namespace crypto_square