#include <iostream>
using namespace std;

namespace hamming {
int compute(string dna1, string dna2) {
  int l = dna1.length();
  int l2 = dna2.length();
  if (l != l2) {
    throw domain_error("2 DNAs have different lengths.");
  }
  int hamming_distance = l;
  for (int i = 0; i < l; i++) {
    if (dna1[i] == dna2[i]) {
      hamming_distance = hamming_distance - 1;
    }
  }
  return hamming_distance;
}

}  // namespace hamming
