#include "nucleotide_count.h"
#include <stdexcept>

namespace nucleotide_count {
counter::counter(const std::string& dnaStrand) {
  try {
    for (char nucleotide : dnaStrand) nucleotides.at(nucleotide) += 1;
  } catch (const std::out_of_range& OUT_OF_RANGE) {
    throw std::invalid_argument("DNA strand has invalid nucleotides.");
  }
}

const std::map<char, int>& counter::nucleotide_counts() const {
  return nucleotides;
}

int counter::count(char nucleotide) const {
  try {
    return nucleotides.at(nucleotide);
  } catch (const std::exception& EXCEPTION) {
    throw std::invalid_argument(
        std::string(" is an invalid nucleotide.").insert(0, 1, nucleotide));
  }
}
}  // namespace nucleotide_count
