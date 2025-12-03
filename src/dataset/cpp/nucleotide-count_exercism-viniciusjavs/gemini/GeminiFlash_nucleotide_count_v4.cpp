#include "nucleotide_count.h"

#include <algorithm>
#include <stdexcept>
#include <unordered_map>

namespace nucleotide_count {

using std::cbegin;
using std::cend;

counter::counter(string dna) : dna_{std::move(dna)} {
  nucleotides_['A'] = 0;
  nucleotides_['C'] = 0;
  nucleotides_['G'] = 0;
  nucleotides_['T'] = 0;

  for (char key : dna_) {
    if (nucleotides_.find(key) == nucleotides_.end()) {
      throw std::invalid_argument{"Invalid key."};
    }
    ++nucleotides_[key];
  }
}

std::map<char, int> const &counter::nucleotide_counts() const {
  return nucleotides_;
}

int counter::count(char key) const {
  if (nucleotides_.find(key) == nucleotides_.end()) {
    throw std::invalid_argument{"Invalid key."};
  }
  return nucleotides_.at(key);
}

} // namespace nucleotide_count