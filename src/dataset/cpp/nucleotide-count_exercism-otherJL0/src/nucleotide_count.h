#if !defined(NUCLEOTIDE_COUNT_H)
#define NUCLEOTIDE_COUNT_H
#include <map>
#include <string>

namespace nucleotide_count {
class counter {
 private:
  std::map<char, int> nucleotides = {{'A', 0}, {'T', 0}, {'C', 0}, {'G', 0}};

 public:
  explicit counter(const std::string& dnaStrand);
  const std::map<char, int>& nucleotide_counts() const;
  int count(char nucleotide) const;
};
}  // namespace nucleotide_count

#endif  // NUCLEOTIDE_COUNT_H
