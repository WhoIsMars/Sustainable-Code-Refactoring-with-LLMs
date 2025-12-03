#include <iostream>
#include <string>
#include <stdexcept>

namespace hamming {
int compute(const std::string& dna1, const std::string& dna2) {
  size_t l = dna1.length();
  if (l != dna2.length()) {
    throw std::domain_error("DNA strings must have the same length.");
  }

  int hamming_distance = 0;
  for (size_t i = 0; i < l; ++i) {
    if (dna1[i] != dna2[i]) {
      hamming_distance++;
    }
  }
  return hamming_distance;
}

}  // namespace hamming