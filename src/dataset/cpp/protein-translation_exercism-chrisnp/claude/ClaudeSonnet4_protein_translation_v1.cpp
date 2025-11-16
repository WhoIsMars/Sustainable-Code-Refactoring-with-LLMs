#include "protein_translation.h"
#include <unordered_map>

namespace {
    constexpr const char* const Methionine = "Methionine";
    constexpr const char* const Phenylalanine = "Phenylalanine";
    constexpr const char* const Leucine = "Leucine";
    constexpr const char* const Serine = "Serine";
    constexpr const char* const Tyrosine = "Tyrosine";
    constexpr const char* const Cysteine = "Cysteine";
    constexpr const char* const Tryptophan = "Tryptophan";
    constexpr const char* const stop = "STOP";

    const std::unordered_map<std::string, const char*> codons_to_proteins {
        {"AUG", Methionine},
        {"UUU", Phenylalanine}, {"UUC", Phenylalanine},
        {"UUA", Leucine}, {"UUG", Leucine},
        {"UCU", Serine}, {"UCC", Serine}, {"UCA", Serine}, 
        {"UCG", Serine},
        {"UAU", Tyrosine}, {"UAC", Tyrosine},
        {"UGU", Cysteine}, {"UGC", Cysteine},
        {"UGG", Tryptophan},
        {"UAA", stop}, {"UAG", stop}, {"UGA", stop},
    };
}

std::vector<std::string> protein_translation::proteins(const std::string& rna) {
    std::vector<std::string> polypeptide;
    polypeptide.reserve(rna.length() / 3);

    for (size_t n = 0; n < rna.length(); n += 3) {
        if (n + 2 >= rna.length()) break;
        
        std::string codon = rna.substr(n, 3);
        auto it = codons_to_proteins.find(codon);
        if (it == codons_to_proteins.end()) continue;
        
        if (it->second == stop) break;
        polypeptide.emplace_back(it->second);
    }
    return polypeptide;
}