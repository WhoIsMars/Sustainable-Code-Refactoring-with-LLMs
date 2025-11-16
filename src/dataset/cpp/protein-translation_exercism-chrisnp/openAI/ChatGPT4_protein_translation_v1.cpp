#include "protein_translation.h"
#include <unordered_map>

const std::unordered_map<std::string_view, std::string_view> codons_to_proteins {
    {"AUG", "Methionine"},
    {"UUU", "Phenylalanine"}, {"UUC", "Phenylalanine"},
    {"UUA", "Leucine"}, {"UUG", "Leucine"},
    {"UCU", "Serine"}, {"UCC", "Serine"}, {"UCA", "Serine"}, 
    {"UCG", "Serine"},
    {"UAU", "Tyrosine"}, {"UAC", "Tyrosine"},
    {"UGU", "Cysteine"}, {"UGC", "Cysteine"},
    {"UGG", "Tryptophan"},
    {"UAA", "STOP"}, {"UAG", "STOP"}, {"UGA", "STOP"},
};

std::vector<std::string> protein_translation::proteins(const std::string& rna) {
    std::vector<std::string> polypeptide;
    polypeptide.reserve(rna.length() / 3); // Reserve space to avoid reallocations

    for (size_t n = 0; n + 2 < rna.size(); n += 3) {
        std::string_view codon = std::string_view(rna).substr(n, 3);
        auto it = codons_to_proteins.find(codon);
        if (it == codons_to_proteins.end() || it->second == "STOP") break;
        polypeptide.emplace_back(it->second);
    }
    return polypeptide;
}