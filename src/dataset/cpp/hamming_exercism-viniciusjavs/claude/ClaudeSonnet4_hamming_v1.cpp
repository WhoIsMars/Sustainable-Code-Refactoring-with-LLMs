#include "hamming.h"

namespace hamming {

int compute(string const &first, string const &second) {
  if (first.length() != second.length())
    throw std::domain_error{"Sequences differ in length."};

  int count = 0;
  const size_t len = first.length();
  
  for (size_t i = 0; i < len; ++i) {
    count += (first[i] != second[i]);
  }
  
  return count;
}

} // namespace hamming