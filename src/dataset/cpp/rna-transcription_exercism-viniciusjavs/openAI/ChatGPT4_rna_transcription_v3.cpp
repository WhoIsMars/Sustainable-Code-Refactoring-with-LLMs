#include "rna_transcription.h"
#include <unordered_map>

namespace rna_transcription {

char to_rna(char dna) {
    switch (dna) {
        case 'G': return 'C';
        case 'C': return 'G';
        case 'T': return 'A';
        case 'A': return 'U';
        default: throw std::invalid_argument("Invalid DNA nucleotide");
    }
}

string to_rna(string strand) {
    for (char &c : strand) {
        c = to_rna(c);
    }
    return strand;
}

} // namespace rna_transcription