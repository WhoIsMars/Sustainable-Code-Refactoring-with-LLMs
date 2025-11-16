#include "rna_transcription.h"

#include <unordered_map>

namespace rna_transcription {

std::string to_rna(const std::string& dna) {
    static const std::unordered_map<char, char> encoding {
        {'G', 'C'},
        {'C', 'G'},
        {'T', 'A'},
        {'A', 'U'}
    };

    std::string rna;
    rna.reserve(dna.size());

    for (char c : dna) {
        rna.push_back(encoding.at(c));
    }

    return rna;
}

char to_rna(char dna) {
    static const std::unordered_map<char, char> encoding {
        {'G', 'C'},
        {'C', 'G'},
        {'T', 'A'},
        {'A', 'U'}
    };

    return encoding.at(dna);
}

}  // namespace rna_transcription