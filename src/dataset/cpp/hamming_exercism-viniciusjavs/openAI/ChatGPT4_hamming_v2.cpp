#include "hamming.h"
#include <stdexcept>

namespace hamming {

int compute(const std::string &first, const std::string &second) {
  if (first.size() != second.size())
    throw std::domain_error{"Sequences differ in length."};

  int distance = 0;
  for (size_t i = 0; i < first.size(); ++i) {
    if (first[i] != second[i]) {
      ++distance;
    }
  }
  return distance;
}

} // namespace hamming