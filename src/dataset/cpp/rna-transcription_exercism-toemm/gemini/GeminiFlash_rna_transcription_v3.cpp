#include "rna_transcription.h"

#include <string>

namespace rna_transcription {

char to_rna(char dna) {
    switch (dna) {
        case 'G': return 'C';
        case 'C': return 'G';
        case 'T': return 'A';
        case 'A': return 'U';
        default: return '\0'; // Or throw an exception for invalid input
    }
}

std::string to_rna(std::string dna) {
    std::string rna;
    rna.reserve(dna.length());

    for (char c : dna) {
        rna += to_rna(c);
    }

    return rna;
}

}  // namespace rna_transcription