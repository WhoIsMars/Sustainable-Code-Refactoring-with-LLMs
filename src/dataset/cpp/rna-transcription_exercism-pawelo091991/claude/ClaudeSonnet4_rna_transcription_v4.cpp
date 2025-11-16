#include "rna_transcription.h"

char transcription::to_rna(char RNA) {
    static constexpr char lookup[256] = {
        ['G'] = 'C',
        ['C'] = 'G', 
        ['T'] = 'A',
        ['A'] = 'U'
    };
    return lookup[static_cast<unsigned char>(RNA)] ?: '?';
}

string transcription::to_rna(string RNA) {
    string newRNA;
    newRNA.reserve(RNA.size());
    for (char c : RNA) {
        newRNA += to_rna(c);
    }
    return newRNA;
}