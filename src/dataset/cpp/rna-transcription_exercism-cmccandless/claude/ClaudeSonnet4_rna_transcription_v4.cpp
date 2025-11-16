#include "rna_transcription.h"

char transcription::to_rna(char ch)
{
    static constexpr char lookup[256] = {
        [0 ... 255] = '\0',
        ['C'] = 'G',
        ['G'] = 'C',
        ['A'] = 'U',
        ['T'] = 'A'
    };
    return lookup[static_cast<unsigned char>(ch)];
}

std::string transcription::to_rna(std::string s)
{
    std::string result;
    result.reserve(s.size());
    for (char ch : s) {
        result += to_rna(ch);
    }
    return result;
}