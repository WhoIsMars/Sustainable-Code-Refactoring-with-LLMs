#include "rna_transcription.h"

char transcription::to_rna(char RNA) {
    switch (RNA) {
        case 'G': return 'C';
        case 'C': return 'G';
        case 'T': return 'A';
        case 'A': return 'U';
        default: return '?';
    }
}

string transcription::to_rna(string RNA) {
    string newRNA;
    newRNA.reserve(RNA.size());
    for (char c : RNA) {
        newRNA += to_rna(c);
    }
    return newRNA;
}