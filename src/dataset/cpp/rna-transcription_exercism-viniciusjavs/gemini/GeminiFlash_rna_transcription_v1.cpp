#include "rna_transcription.h"
#include <algorithm>
#include <string>
#include <unordered_map>

namespace rna_transcription {

char to_rna(char dna) {
  switch (dna) {
  case 'G':
    return 'C';
  case 'C':
    return 'G';
  case 'T':
    return 'A';
  case 'A':
    return 'U';
  default:
    return dna; // Or throw an exception for invalid input
  }
}

std::string to_rna(const std::string& strand) {
  std::string rna;
  rna.reserve(strand.length());
  for (char dna : strand) {
    rna += to_rna(dna);
  }
  return rna;
}

} // namespace rna_transcription