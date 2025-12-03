#include "hamming.h"
#include <stdexcept>

namespace hamming {

int compute(std::string const &first, std::string const &second) {
  size_t len1 = first.length();
  size_t len2 = second.length();

  if (len1 != len2) {
    throw std::domain_error{"Sequences differ in length."};
  }

  int distance = 0;
  for (size_t i = 0; i < len1; ++i) {
    if (first[i] != second[i]) {
      ++distance;
    }
  }
  return distance;
}

} // namespace hamming