#include "rna_transcription.h"

namespace transcription {
    char to_rna(char dna)
    {
        static constexpr char lookup[256] = {
            ['A'] = 'U',
            ['C'] = 'G', 
            ['G'] = 'C',
            ['T'] = 'A'
        };
        return lookup[static_cast<unsigned char>(dna)];
    }

    std::string to_rna(std::string str)
    {
        for (char& c : str) {
            c = to_rna(c);
        }
        return str;
    }
}