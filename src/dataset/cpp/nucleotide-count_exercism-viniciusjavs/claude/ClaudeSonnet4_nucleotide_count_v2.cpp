#include "nucleotide_count.h"

#include <stdexcept>

namespace nucleotide_count {

bool counter::valid_key(char key) const {
  return key == 'A' || key == 'C' || key == 'G' || key == 'T';
}

void counter::validate_key(char key) const {
  if (!valid_key(key))
    throw std::invalid_argument{"Invalid key."};
}

counter::counter(string dna) : dna_{std::move(dna)} {
  nucleotides_['A'] = 0;
  nucleotides_['C'] = 0;
  nucleotides_['G'] = 0;
  nucleotides_['T'] = 0;
  
  for (char key : dna_) {
    validate_key(key);
    ++nucleotides_[key];
  }
}

std::map<char, int> const &counter::nucleotide_counts() const {
  return nucleotides_;
}

int counter::count(char key) const {
  validate_key(key);
  auto it = nucleotides_.find(key);
  return it != nucleotides_.end() ? it->second : 0;
}

} // namespace nucleotide_count