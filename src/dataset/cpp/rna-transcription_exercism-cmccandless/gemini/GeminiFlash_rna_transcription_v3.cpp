#include "rna_transcription.h"
#include <string>
#include <algorithm>

char transcription::to_rna(char ch) {
  switch (ch) {
    case 'C': return 'G';
    case 'G': return 'C';
    case 'A': return 'U';
    case 'T': return 'A';
    default: return '\0';
  }
}

std::string transcription::to_rna(std::string s) {
  std::string result(s.size(), '\0');
  std::transform(s.begin(), s.end(), result.begin(), [](char c){
    switch (c) {
      case 'C': return 'G';
      case 'G': return 'C';
      case 'A': return 'U';
      case 'T': return 'A';
      default: return '\0';
    }
  });
  return result;
}