#include "hamming.h"

namespace hamming {
  int compute(const std::string& strand1, const std::string& strand2) {
    if (strand1.length() != strand2.length()) {
      throw std::domain_error("Strand lengths do not match.");
    }

    int count = 0;
    const char* s1 = strand1.data();
    const char* s2 = strand2.data();
    const size_t len = strand1.length();
    
    for (size_t i = 0; i < len; ++i) {
      count += (s1[i] != s2[i]);
    }
    
    return count;
  }
} // namespace hamming