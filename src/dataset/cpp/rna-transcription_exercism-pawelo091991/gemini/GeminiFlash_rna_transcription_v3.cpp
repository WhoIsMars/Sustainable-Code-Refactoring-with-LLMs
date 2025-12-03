#include "rna_transcription.h"
#include <unordered_map>

char transcription::to_rna(char dna) {
    static const std::unordered_map<char, char> dna_to_rna = {
        {'G', 'C'},
        {'C', 'G'},
        {'T', 'A'},
        {'A', 'U'}
    };

    auto it = dna_to_rna.find(dna);
    return (it != dna_to_rna.end()) ? it->second : '?';
}

string transcription::to_rna(string dna) {
    string rna;
    rna.reserve(dna.length());
    for (char nucleotide : dna) {
        rna += to_rna(nucleotide);
    }
    return rna;
}