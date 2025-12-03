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
  std::string result;
  result.reserve(s.length());
  for (char ch : s) {
    char rna_char = to_rna(ch);
    if (rna_char != '\0') {
      result += rna_char;
    }
  }
  return result;
}