#include "rna_transcription.h"

#include <unordered_map>

namespace rna_transcription {

std::string to_rna(std::string dna) {
    std::string rna;
    rna.reserve(dna.size()); // Reserve memory to avoid reallocations

    for (char c : dna) {
        switch (c) {
            case 'G': rna += 'C'; break;
            case 'C': rna += 'G'; break;
            case 'T': rna += 'A'; break;
            case 'A': rna += 'U'; break;
        }
    }

    return rna;
}

char to_rna(char dna) {
    switch (dna) {
        case 'G': return 'C';
        case 'C': return 'G';
        case 'T': return 'A';
        case 'A': return 'U';
        default: return '\0'; // Handle invalid input
    }
}

}  // namespace rna_transcription