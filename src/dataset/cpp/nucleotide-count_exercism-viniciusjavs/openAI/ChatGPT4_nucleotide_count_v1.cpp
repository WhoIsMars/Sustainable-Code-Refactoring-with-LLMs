#include "nucleotide_count.h"

#include <array>
#include <stdexcept>
#include <unordered_map>

namespace nucleotide_count {

bool counter::valid_key(char key) const {
  return key == 'A' || key == 'C' || key == 'G' || key == 'T';
}

void counter::validate_key(char key) const {
  if (!valid_key(key))
    throw std::invalid_argument{"Invalid key."};
}

counter::counter(string dna) : dna_{std::move(dna)}, nucleotides_{{'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}} {
  for (char key : dna_) {
    validate_key(key);
    ++nucleotides_[key];
  }
}

const std::unordered_map<char, int>& counter::nucleotide_counts() const {
  return nucleotides_;
}

int counter::count(char key) const {
  validate_key(key);
  return nucleotides_.at(key);
}

} // namespace nucleotide_count