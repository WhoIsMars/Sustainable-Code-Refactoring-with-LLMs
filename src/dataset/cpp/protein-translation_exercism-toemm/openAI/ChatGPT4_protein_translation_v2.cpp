#include "protein_translation.h"

#include <unordered_map>
#include <vector>

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
        out.reserve(rna.size() / 3); // Reserve memory upfront to avoid reallocations

        for (std::size_t i = 0; i + 2 < rna.size(); i += 3) { // Ensure valid codon length
            auto it = codon_table.find(rna.substr(i, 3));
            if (it == codon_table.end() || it->second.empty()) break; // Stop on invalid or stop codon
            out.push_back(it->second);
        }

        return out;
    }

}  // namespace protein_translation