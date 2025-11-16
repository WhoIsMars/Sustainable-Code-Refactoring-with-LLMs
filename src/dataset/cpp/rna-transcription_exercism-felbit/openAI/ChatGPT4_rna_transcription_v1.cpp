#include "rna_transcription.h"

namespace transcription {
    char to_rna(char dna)
    {
        if (dna == 'C') return 'G';
        if (dna == 'G') return 'C';
        if (dna == 'A') return 'U';
        return 'A'; // Covers 'T' and default case
    }

    std::string to_rna(std::string str)
    {
        for (char &c : str) {
            c = to_rna(c);
        }
        return str;
    }
}