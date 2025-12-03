#include "rna_transcription.h"
#include <string>
#include <unordered_map>

namespace rna_transcription {

char to_rna(char dna) {
  static constexpr std::unordered_map<char, char> dna_to_rna = {
      {'G', 'C'}, {'C', 'G'}, {'T', 'A'}, {'A', 'U'}};
  auto it = dna_to_rna.find(dna);
  if (it != dna_to_rna.end()) {
    return it->second;
  }
  return dna; // Or throw an exception for invalid input, depending on requirements
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