#include "hamming.h"
#include <stdexcept>

namespace hamming {
  int compute(const std::string& strand1, const std::string& strand2) {
    if (strand1.length() != strand2.length()) {
      throw std::domain_error("Strand lengths do not match.");
    }

    int distance = 0;
    for (size_t i = 0; i < strand1.length(); ++i) {
      if (strand1[i] != strand2[i]) {
        ++distance;
      }
    }
    return distance;
  }
} // namespace hamming