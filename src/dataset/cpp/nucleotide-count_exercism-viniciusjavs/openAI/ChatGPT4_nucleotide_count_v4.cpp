#include "nucleotide_count.h"

#include <array>
#include <stdexcept>
#include <unordered_map>

namespace nucleotide_count {

class counter {
public:
  explicit counter(const std::string &dna) : nucleotides_{{'A', 0}, {'C', 0}, {'G', 0}, {'T', 0}} {
    for (char key : dna) {
      if (!valid_key(key)) throw std::invalid_argument{"Invalid key."};
      ++nucleotides_[key];
    }
  }

  const std::unordered_map<char, int> &nucleotide_counts() const {
    return nucleotides_;
  }

  int count(char key) const {
    if (!valid_key(key)) throw std::invalid_argument{"Invalid key."};
    return nucleotides_.at(key);
  }

private:
  static constexpr std::array<char, 4> valid_keys_ = {'A', 'C', 'G', 'T'};

  static bool valid_key(char key) {
    return std::find(valid_keys_.begin(), valid_keys_.end(), key) != valid_keys_.end();
  }

  std::unordered_map<char, int> nucleotides_;
};

} // namespace nucleotide_count