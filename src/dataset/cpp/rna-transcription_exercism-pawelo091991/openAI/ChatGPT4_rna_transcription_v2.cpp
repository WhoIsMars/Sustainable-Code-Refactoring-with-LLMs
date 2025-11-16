#include "rna_transcription.h"
#include <unordered_map>

char transcription::to_rna(char RNA) {
    static const std::unordered_map<char, char> rna_map = {
        {'G', 'C'}, {'C', 'G'}, {'T', 'A'}, {'A', 'U'}
    };
    auto it = rna_map.find(RNA);
    return it != rna_map.end() ? it->second : '?';
}

string transcription::to_rna(const string& RNA) {
    string newRNA;
    newRNA.reserve(RNA.size());
    for (char kv : RNA) newRNA.push_back(to_rna(kv));
    return newRNA;
}