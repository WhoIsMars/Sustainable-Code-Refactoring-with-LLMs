#include "protein_translation.h"
#include <unordered_map>
#include <string_view>

namespace {
    constexpr std::string_view Methionine {"Methionine"};
    constexpr std::string_view Phenylalanine {"Phenylalanine"};
    constexpr std::string_view Leucine {"Leucine"};
    constexpr std::string_view Serine {"Serine"};
    constexpr std::string_view Tyrosine {"Tyrosine"};
    constexpr std::string_view Cysteine {"Cysteine"};
    constexpr std::string_view Tryptophan {"Tryptophan"};
    constexpr std::string_view stop {"STOP"};

    const std::unordered_map<std::string_view, std::string_view> codons_to_proteins {
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

    for (size_t n = 0; n + 2 < rna.length(); n += 3) {
        std::string_view codon{rna.data() + n, 3};
        auto it = codons_to_proteins.find(codon);
        if (it == codons_to_proteins.end()) continue;
        
        if (it->second == stop) break;
        polypeptide.emplace_back(it->second);
    }
    return polypeptide;
}