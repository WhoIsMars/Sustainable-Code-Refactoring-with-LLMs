#include "rna_transcription.h"

#include <iostream>
#include <unordered_map>
#include <string>

namespace rna_transcription {
const std::unordered_map<char, char> rna_map = {{'A', 'U'}, {'C', 'G'}, {'G', 'C'}, {'T', 'A'}};

char to_rna(char dna) {
    return rna_map.at(dna);
}

const std::string to_rna(const std::string& dna) {
    std::string rna;
    rna.reserve(dna.size());
    for (const char& c : dna) {
        rna.push_back(rna_map.at(c));
    }
    std::cout << rna;
    return rna;
}
}  // namespace rna_transcription