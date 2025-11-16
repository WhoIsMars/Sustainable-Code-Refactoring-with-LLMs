#include "protein_translation.h"
#include <unordered_map>

const std::string Methionine {"Methionine"};
const std::string Phenylalanine {"Phenylalanine"};
const std::string Leucine {"Leucine"};
const std::string Serine {"Serine"};
const std::string Tyrosine {"Tyrosine"};
const std::string Cysteine {"Cysteine"};
const std::string Tryptophan {"Tryptophan"};
const std::string stop {"STOP"};

const std::unordered_map<std::string, std::string> codons_to_proteins {
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

std::vector<std::string> protein_translation::proteins(const std::string& rna) {
    std::vector<std::string> polypeptide;
    polypeptide.reserve(rna.length() / 3); // Reserve space to avoid reallocations

    for (size_t n = 0; n + 2 < rna.length(); n += 3) {
        auto it = codons_to_proteins.find(rna.substr(n, 3));
        if (it == codons_to_proteins.end() || it->second == stop) break;
        polypeptide.push_back(it->second);
    }
    return polypeptide;
}