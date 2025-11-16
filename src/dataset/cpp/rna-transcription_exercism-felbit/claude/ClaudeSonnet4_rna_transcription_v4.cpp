#include "rna_transcription.h"

namespace transcription {
    char to_rna(char dna)
    {
        switch (dna)
        {
        case 'C':
            return 'G';
        case 'G':
            return 'C';
        case 'A':
            return 'U';
        case 'T':
        default:
            return 'A';
        }
    }

    std::string to_rna(std::string str)
    {
        for (char &c : str) {
            c = to_rna(c);
        }
        return str;
    }
}