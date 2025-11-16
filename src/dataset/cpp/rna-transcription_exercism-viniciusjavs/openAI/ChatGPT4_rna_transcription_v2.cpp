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

string to_rna(const string& strand) {
    string rna;
    rna.reserve(strand.size());
    for (char nucleotide : strand) {
        rna.push_back(to_rna(nucleotide));
    }
    return rna;
}

} // namespace rna_transcription