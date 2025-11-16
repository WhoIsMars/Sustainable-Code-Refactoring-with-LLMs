#include "rna_transcription.h"

#include <iostream>
#include <string>

using namespace std;
namespace rna_transcription {

char to_rna(char dna) { 
    switch (dna) {
        case 'A': return 'U';
        case 'C': return 'G';
        case 'G': return 'C';
        case 'T': return 'A';
        default: return dna;
    }
}

const string to_rna(string const dna) {
    string rna;
    rna.reserve(dna.size());
    for (const char& c : dna) {
        rna += to_rna(c);
    }
    cout << rna;
    return rna;
}

}  // namespace rna_transcription