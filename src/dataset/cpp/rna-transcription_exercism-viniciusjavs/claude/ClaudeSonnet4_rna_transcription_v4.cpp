#include "rna_transcription.h"
#include <algorithm>

namespace rna_transcription {

constexpr char to_rna(char dna) noexcept {
    switch (dna) {
        case 'G': return 'C';
        case 'C': return 'G';
        case 'T': return 'A';
        case 'A': return 'U';
        default: return dna;
    }
}

string to_rna(string strand) {
    std::transform(strand.cbegin(), strand.cend(), strand.begin(), to_rna);
    return strand;
}

} // namespace rna_transcription