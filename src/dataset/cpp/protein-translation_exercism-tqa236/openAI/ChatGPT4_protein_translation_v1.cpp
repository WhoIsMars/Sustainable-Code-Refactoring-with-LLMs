#include "protein_translation.h"

#include <unordered_map>

namespace protein_translation {

const std::unordered_map<codon, polypeptide> translator = {
    {"AUG", "Methionine"}, {"UUU", "Phenylalanine"}, {"UUC", "Phenylalanine"},
    {"UUA", "Leucine"},    {"UUG", "Leucine"},       {"UCU", "Serine"},
    {"UCC", "Serine"},     {"UCA", "Serine"},        {"UCG", "Serine"},
    {"UAU", "Tyrosine"},   {"UAC", "Tyrosine"},      {"UGU", "Cysteine"},
    {"UGC", "Cysteine"},   {"UGG", "Tryptophan"},    {"UAA", "STOP"},
    {"UAG", "STOP"},       {"UGA", "STOP"}};

std::vector<codon> proteins(const ARN& arn) {
  std::vector<polypeptide> protein_names;
  protein_names.reserve(arn.length() / 3);  // Reserve memory upfront
  for (size_t i = 0, n = arn.length(); i + 2 < n; i += 3) {
    auto it = translator.find(arn.substr(i, 3));
    if (it == translator.end() || it->second == "STOP") break;
    protein_names.push_back(it->second);
  }
  return protein_names;
}

}  // namespace protein_translation