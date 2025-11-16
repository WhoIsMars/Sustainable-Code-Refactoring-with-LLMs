#include "hamming.h"
#include <stdexcept>

namespace hamming {
  int compute(const std::string& strand1, const std::string& strand2) {
    size_t len1 = strand1.length();
    size_t len2 = strand2.length();

    if (len1 != len2) {
      throw std::domain_error("Strand lengths do not match.");
    }

    int distance = 0;
    for (size_t i = 0; i < len1; ++i) {
      if (strand1[i] != strand2[i]) {
        ++distance;
      }
    }
    return distance;
  }
} // namespace hamming