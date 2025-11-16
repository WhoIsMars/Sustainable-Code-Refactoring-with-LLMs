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
  for (unsigned i = 0; i < arn.length(); i = i + 3) {
    std::string protein = translator.at(arn.substr(i, 3));
    if (protein == "STOP") break;
    protein_names.push_back(protein);
  };
  return protein_names;
}

}  // namespace protein_translation
