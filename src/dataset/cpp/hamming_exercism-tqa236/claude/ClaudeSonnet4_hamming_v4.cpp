#include <stdexcept>
#include <string>

namespace hamming {
int compute(const std::string& dna1, const std::string& dna2) {
  const std::size_t l = dna1.length();
  if (l != dna2.length()) {
    throw std::domain_error("2 DNAs have different lengths.");
  }
  int hamming_distance = 0;
  for (std::size_t i = 0; i < l; ++i) {
    if (dna1[i] != dna2[i]) {
      ++hamming_distance;
    }
  }
  return hamming_distance;
}
}  // namespace hamming