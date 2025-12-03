#include "rna_transcription.h"

char transcription::to_rna(char ch)
{
    switch (ch)
    {
    case 'C': return 'G';
    case 'G': return 'C';
    case 'A': return 'U';
    case 'T': return 'A';
    default: return '\0';
    }
}

std::string transcription::to_rna(const std::string& s)
{
    std::string result;
    result.reserve(s.size());
    for (char ch : s) {
        result.push_back(to_rna(ch));
    }
    return result;
}