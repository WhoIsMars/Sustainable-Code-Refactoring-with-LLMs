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

std::string transcription::to_rna(std::string s)
{
    for (auto &ch : s) {
        ch = to_rna(ch);
    }
    return s;
}