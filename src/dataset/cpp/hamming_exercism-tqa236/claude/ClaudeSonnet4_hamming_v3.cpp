#include <iostream>
#include <stdexcept>
using namespace std;

namespace hamming {
int compute(const string& dna1, const string& dna2) {
  if (dna1.length() != dna2.length()) {
    throw domain_error("2 DNAs have different lengths.");
  }
  
  int hamming_distance = 0;
  const size_t length = dna1.length();
  
  for (size_t i = 0; i < length; ++i) {
    if (dna1[i] != dna2[i]) {
      ++hamming_distance;
    }
  }
  
  return hamming_distance;
}
}  // namespace hamming