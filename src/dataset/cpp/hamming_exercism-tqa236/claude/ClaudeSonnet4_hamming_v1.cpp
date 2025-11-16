#include <iostream>
using namespace std;

namespace hamming {
int compute(const string& dna1, const string& dna2) {
  const size_t l = dna1.length();
  if (l != dna2.length()) {
    throw domain_error("2 DNAs have different lengths.");
  }
  int hamming_distance = 0;
  for (size_t i = 0; i < l; ++i) {
    if (dna1[i] != dna2[i]) {
      ++hamming_distance;
    }
  }
  return hamming_distance;
}
}  // namespace hamming