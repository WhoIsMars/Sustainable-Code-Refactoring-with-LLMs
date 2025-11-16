#include "hamming.h"
#include <stdexcept>

namespace hamming {

int compute(const std::string &first, const std::string &second) {
  if (first.size() != second.size())
    throw std::domain_error("Sequences differ in length.");

  int distance = 0;
  for (size_t i = 0; i < first.size(); ++i) {
    distance += (first[i] != second[i]);
  }
  return distance;
}

} // namespace hamming