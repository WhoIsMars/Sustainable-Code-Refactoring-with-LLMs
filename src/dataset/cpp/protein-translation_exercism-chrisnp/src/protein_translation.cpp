#include "protein_translation.h"
#include <map>

const std::string Methionine {"Methionine"};
const std::string Phenylalanine {"Phenylalanine"};
const std::string Leucine {"Leucine"};
const std::string Serine {"Serine"};
const std::string Tyrosine {"Tyrosine"};
const std::string Cysteine {"Cysteine"};
const std::string Tryptophan {"Tryptophan"};
const std::string stop {"STOP"};

const std::map<std::string, std::string> codons_to_proteins {
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
    std::vector<string> polypeptide {};

    for (unsigned int n{0}; n < rna.length(); n += 3) {
        std::string codon = rna.substr(n, 3);
        const std::string& protein = codons_to_proteins.at(codon);
        if (protein == stop) break;
        polypeptide.push_back(protein);
    }
    return polypeptide;
}



