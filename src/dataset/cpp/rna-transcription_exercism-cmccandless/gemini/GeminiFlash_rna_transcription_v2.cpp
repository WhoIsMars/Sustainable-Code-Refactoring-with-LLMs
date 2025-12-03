#include "rna_transcription.h"
#include <string>
#include <algorithm>

char transcription::to_rna(char ch) {
  switch (ch) {
    case 'C': return 'G';
    case 'G': return 'C';
    case 'A': return 'U';
    case 'T': return 'A';
    default: return '\0'; // Explicitly handle default case
  }
}

std::string transcription::to_rna(std::string s) {
  std::string result = s; // Create a copy to modify in-place

  std::transform(result.begin(), result.end(), result.begin(), [](char c) {
    switch (c) {
      case 'C': return 'G';
      case 'G': return 'C';
      case 'A': return 'U';
      case 'T': return 'A';
      default: return '\0'; // Or handle invalid characters as needed, e.g., throw an exception
    }
  });

  return result;
}