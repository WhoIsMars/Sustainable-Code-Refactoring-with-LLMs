#include "nucleotide_count.h"

#include <array>
#include <stdexcept>
#include <unordered_map>

namespace nucleotide_count {

class counter {
public:
  counter(const std::string &dna) : nucleotides_{{'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}} {
    for (char key : dna) {
      if (!valid_key(key)) {
        throw std::invalid_argument{"Invalid key."};
      }
      ++nucleotides_[key];
    }
  }

  const std::unordered_map<char, int> &nucleotide_counts() const {
    return nucleotides_;
  }

  int count(char key) const {
    if (!valid_key(key)) {
      throw std::invalid_argument{"Invalid key."};
    }
    return nucleotides_.at(key);
  }

private:
  static bool valid_key(char key) {
    return key == 'A' || key == 'C' || key == 'G' || key == 'T';
  }

  std::unordered_map<char, int> nucleotides_;
};

} // namespace nucleotide_count