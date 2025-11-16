#include "rna_transcription.h"

#include <string>
#include <unordered_map>

namespace rna_transcription {

std::string to_rna(std::string dna) {
    std::string rna;
    rna.reserve(dna.length());

    static const std::unordered_map<char, char> encoding = {
        {'G', 'C'},
        {'C', 'G'},
        {'T', 'A'},
        {'A', 'U'}
    };

    for (char c : dna) {
        auto it = encoding.find(c);
        if (it != encoding.end()) {
            rna += it->second;
        }
    }

    return rna;
}

}  // namespace rna_transcription