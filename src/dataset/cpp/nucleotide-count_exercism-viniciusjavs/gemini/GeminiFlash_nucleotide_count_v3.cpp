#include "nucleotide_count.h"

#include <algorithm>
#include <stdexcept>
#include <array>

namespace nucleotide_count {

using std::cbegin;
using std::cend;

bool counter::valid_key(char key) const {
  constexpr std::array<char, 4> keys = {'A', 'C', 'G', 'T'};
  return std::any_of(keys.cbegin(), keys.cend(),
                     [key](auto k) { return key == k; });
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
  return nucleotides_.at(key);
}

} // namespace nucleotide_count