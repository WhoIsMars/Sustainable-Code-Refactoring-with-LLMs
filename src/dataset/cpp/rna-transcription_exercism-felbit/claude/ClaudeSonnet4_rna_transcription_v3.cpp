#include "rna_transcription.h"

namespace transcription {
    char to_rna(char dna)
    {
        constexpr char lookup[256] = {
            ['C'] = 'G',
            ['G'] = 'C', 
            ['A'] = 'U',
            ['T'] = 'A'
        };
        return lookup[static_cast<unsigned char>(dna)] ?: 'A';
    }

    std::string to_rna(std::string str)
    {
        constexpr char lookup[256] = {
            ['C'] = 'G',
            ['G'] = 'C',
            ['A'] = 'U', 
            ['T'] = 'A'
        };
        
        for (char& c : str) {
            char mapped = lookup[static_cast<unsigned char>(c)];
            c = mapped ? mapped : 'A';
        }
        return str;
    }
}