#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

namespace crypto_square {

cipher::cipher(std::string text) : initial(std::move(text)) {}

std::string cipher::normalize_plain_text() {
  std::string result;
  result.reserve(initial.length()); // Reserve space to avoid reallocations

  for (char c : initial) {
    if (std::isalnum(c)) {
      result += std::tolower(c);
    }
  }

  return normalized_text = result; // Store normalized text
}

unsigned int cipher::size() {
  if (normalized_text.empty()) {
    normalize_plain_text(); // Ensure normalized_text is populated
  }
  if (cached_size == 0) {
    cached_size = calculate_size(normalized_text);
  }
  return cached_size;
}

unsigned int cipher::calculate_size(const std::string& text) {
  size_t text_length = text.length();
  if (text_length == 0) return 0;
  return static_cast<unsigned int>(std::ceil(std::sqrt(text_length)));
}

std::vector<std::string> cipher::plain_text_segments() {
  if (normalized_text.empty()) {
    normalize_plain_text();
  }
  if (!plain_segments.empty()) {
    return plain_segments;
  }

  unsigned int segment_size = size();
  std::vector<std::string> segments;
  segments.reserve((normalized_text.length() + segment_size - 1) /
                    segment_size); // Reserve space

  for (size_t i = 0; i < normalized_text.length(); i += segment_size) {
    segments.emplace_back(normalized_text.substr(i, segment_size));
  }
  plain_segments = segments;
  return plain_segments;
}

std::string cipher::cipher_text() {
  if (!cached_cipher_text.empty()) {
    return cached_cipher_text;
  }
  const auto& segments = plain_text_segments();
  if (segments.empty()) {
    return "";
  }

  unsigned int rows = segments.size();
  unsigned int columns = size();

  std::string result;
  result.reserve(normalized_text.length());

  for (unsigned int column = 0; column < columns; ++column) {
    for (unsigned int row = 0; row < rows; ++row) {
      if (column < segments[row].length()) {
        result += segments[row][column];
      }
    }
  }
  cached_cipher_text = result;
  return result;
}

std::string cipher::normalized_cipher_text() {
  if (!cached_normalized_cipher_text.empty()) {
    return cached_normalized_cipher_text;
  }
  std::string encoded = cipher_text();
  unsigned int segment_size = size();

  std::string result;
  result.reserve(encoded.length() +
                   (encoded.length() / segment_size)); // Reserve space

  for (size_t i = 0; i < encoded.length(); ++i) {
    result += encoded[i];
    if ((i + 1) % segment_size == 0 && i + 1 < encoded.length()) {
      result += ' ';
    }
  }
  cached_normalized_cipher_text = result;
  return result;
}

} // namespace crypto_square