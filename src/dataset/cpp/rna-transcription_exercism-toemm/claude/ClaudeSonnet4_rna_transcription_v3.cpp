#include "rna_transcription.h"

namespace rna_transcription {

char to_rna(char dna) {
    switch (dna) {
        case 'G': return 'C';
        case 'C': return 'G';
        case 'T': return 'A';
        case 'A': return 'U';
        default: return dna;
    }
}

std::string to_rna(std::string dna) {
    std::string rna;
    rna.reserve(dna.size());
    
    for (char c : dna) {
        rna += to_rna(c);
    }
    
    return rna;
}

}  // namespace rna_transcription