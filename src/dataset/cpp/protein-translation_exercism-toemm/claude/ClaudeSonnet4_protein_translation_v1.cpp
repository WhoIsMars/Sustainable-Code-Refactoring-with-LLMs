#include "protein_translation.h"

#include <unordered_map>

namespace protein_translation {

    const std::unordered_map<std::string, std::string> codon_table{
        {"AUG", "Methionine"},
        {"UUU", "Phenylalanine"}, {"UUC", "Phenylalanine"},
        {"UUA", "Leucine"}, {"UUG", "Leucine"},
        {"UCU", "Serine"}, {"UCC", "Serine"}, {"UCA", "Serine"}, {"UCG", "Serine"},
        {"UAU", "Tyrosine"}, {"UAC", "Tyrosine"},
        {"UGU", "Cysteine"}, {"UGC", "Cysteine"},
        {"UGG", "Tryptophan"},
        {"UAA", ""}, {"UAG", ""}, {"UGA", ""}
    };

std::vector<std::string> proteins(const std::string& rna) {
    std::vector<std::string> out;
    out.reserve(rna.size() / 3);

    for (std::size_t i = 0; i + 2 < rna.size(); i += 3) {
        const std::string codon = rna.substr(i, 3);
        
        const auto it = codon_table.find(codon);
        if (it == codon_table.end() || it->second.empty()) {
            break;
        }
        
        out.push_back(it->second);
    }

    return out;
}

}  // namespace protein_translation