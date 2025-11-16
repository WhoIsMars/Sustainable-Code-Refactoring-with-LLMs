#include "rna_transcription.h"

#include <unordered_map>
#include <string>

namespace rna_transcription {
const std::unordered_map<char, char> rna_map = {{'A', 'U'}, {'C', 'G'}, {'G', 'C'}, {'T', 'A'}};

char to_rna(char dna) {
    auto it = rna_map.find(dna);
    return it != rna_map.end() ? it->second : '\0';
}

std::string to_rna(const std::string& dna) {
    std::string rna;
    rna.reserve(dna.size());
    for (const char& c : dna) {
        rna.push_back(to_rna(c));
    }
    return rna;
}
}  // namespace rna_transcription