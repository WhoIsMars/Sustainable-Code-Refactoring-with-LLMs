#include "rna_transcription.h"
#include <algorithm>
#include <string>
#include <unordered_map>

namespace transcription {

    char to_rna(char dna) {
        static const std::unordered_map<char, char> dna_to_rna = {
            {'C', 'G'},
            {'G', 'C'},
            {'A', 'U'},
            {'T', 'A'}
        };

        auto it = dna_to_rna.find(dna);
        return (it != dna_to_rna.end()) ? it->second : 'A';
    }

    std::string to_rna(std::string dna) {
        std::string rna = dna;
        std::transform(dna.begin(), dna.end(), rna.begin(), to_rna);
        return rna;
    }
}