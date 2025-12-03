#include "rna_transcription.h"

char transcription::to_rna(char dna) {
  switch (dna) {
    case 'G': return 'C';
    case 'C': return 'G';
    case 'T': return 'A';
    case 'A': return 'U';
    default: return '?';
  }
}

std::string transcription::to_rna(std::string dna) {
  std::string rna;
  rna.reserve(dna.length());
  for (char nucleotide : dna) {
    rna += to_rna(nucleotide);
  }
  return rna;
}