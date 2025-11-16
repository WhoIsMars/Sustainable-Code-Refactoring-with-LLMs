#include "hamming.h"
#include <stdexcept>

namespace hamming {
  int compute(const std::string& strand1, const std::string& strand2) {
    const auto len = strand1.length();
    if (len != strand2.length()) {
      throw std::domain_error("Strand lengths do not match.");
    }

    int distance = 0;
    const char* s1 = strand1.data();
    const char* s2 = strand2.data();
    
    for (std::size_t i = 0; i < len; ++i) {
      distance += (s1[i] != s2[i]);
    }
    
    return distance;
  }
} // namespace hamming