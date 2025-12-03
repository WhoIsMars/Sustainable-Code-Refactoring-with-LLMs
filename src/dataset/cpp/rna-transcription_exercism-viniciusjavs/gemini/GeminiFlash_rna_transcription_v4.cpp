#include "rna_transcription.h"
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

namespace rna_transcription {

char to_rna(char dna) {
  static const std::unordered_map<char, char> dna_to_rna = {
      {'G', 'C'}, {'C', 'G'}, {'T', 'A'}, {'A', 'U'}};
  auto it = dna_to_rna.find(dna);
  if (it != dna_to_rna.end()) {
    return it->second;
  }
  return dna;
}

string to_rna(string strand) {
  std::string rna_strand(strand.size(), ' ');
  std::transform(strand.begin(), strand.end(), rna_strand.begin(), to_rna);
  return rna_strand;
}

} // namespace rna_transcription