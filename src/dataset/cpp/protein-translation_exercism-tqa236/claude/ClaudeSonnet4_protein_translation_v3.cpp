#include "protein_translation.h"

#include <unordered_map>
#include <string_view>

namespace protein_translation {

const std::unordered_map<std::string_view, std::string_view> translator = {
    {"AUG", "Methionine"}, {"UUU", "Phenylalanine"}, {"UUC", "Phenylalanine"},
    {"UUA", "Leucine"},    {"UUG", "Leucine"},       {"UCU", "Serine"},
    {"UCC", "Serine"},     {"UCA", "Serine"},        {"UCG", "Serine"},
    {"UAU", "Tyrosine"},   {"UAC", "Tyrosine"},      {"UGU", "Cysteine"},
    {"UGC", "Cysteine"},   {"UGG", "Tryptophan"},    {"UAA", "STOP"},
    {"UAG", "STOP"},       {"UGA", "STOP"}};

std::vector<codon> proteins(const ARN& arn) {
    if (arn.empty()) return {};
    
    std::vector<polypeptide> protein_names;
    protein_names.reserve(arn.length() / 3);
    
    for (size_t i = 0; i + 2 < arn.length(); i += 3) {
        std::string_view codon_view = std::string_view(arn).substr(i, 3);
        auto it = translator.find(codon_view);
        if (it == translator.end()) continue;
        
        if (it->second == "STOP") break;
        protein_names.emplace_back(it->second);
    }
    
    return protein_names;
}

}  // namespace protein_translation