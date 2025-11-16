#include "rna_transcription.h"

char transcription::to_rna(char RNA) {
    static const char lookup[256] = {
        ['G'] = 'C',
        ['C'] = 'G', 
        ['T'] = 'A',
        ['A'] = 'U'
    };
    return lookup[RNA] ? lookup[RNA] : '?';
}

string transcription::to_rna(string RNA) {
    string newRNA;
    newRNA.reserve(RNA.size());
    for (char c : RNA) {
        newRNA += to_rna(c);
    }
    return newRNA;
}