#include "rna_transcription.h"
#include <unordered_map>

namespace transcription {

char to_rna(char dna) {
    static const std::unordered_map<char, char> dna_to_rna = {
        {'G', 'C'},
        {'C', 'G'},
        {'T', 'A'},
        {'A', 'U'}
    };

    auto it = dna_to_rna.find(dna);
    return it != dna_to_rna.end() ? it->second : '?';
}

std::string to_rna(const std::string& dna) {
    std::string rna;
    rna.reserve(dna.length());
    for (char nucleotide : dna) {
        rna += to_rna(nucleotide);
    }
    return rna;
}

}  // namespace transcription