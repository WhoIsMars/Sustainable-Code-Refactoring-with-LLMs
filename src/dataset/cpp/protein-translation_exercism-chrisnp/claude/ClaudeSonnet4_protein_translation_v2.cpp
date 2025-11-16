#include "protein_translation.h"
#include <unordered_map>

namespace {
    const std::unordered_map<std::string, std::string> codons_to_proteins {
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
}

std::vector<std::string> protein_translation::proteins(const std::string& rna) {
    std::vector<std::string> polypeptide;
    polypeptide.reserve(rna.length() / 3);

    for (size_t n = 0; n < rna.length(); n += 3) {
        auto it = codons_to_proteins.find(rna.substr(n, 3));
        if (it == codons_to_proteins.end()) continue;
        
        if (it->second == "STOP") break;
        polypeptide.push_back(it->second);
    }
    return polypeptide;
}