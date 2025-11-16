#include "hamming.h"
#include <cstddef>

namespace hamming {

int compute(string const &first, string const &second) {
  const std::size_t len = first.length();
  if (len != second.length())
    throw std::domain_error{"Sequences differ in length."};

  int count = 0;
  const char* ptr1 = first.data();
  const char* ptr2 = second.data();
  
  for (std::size_t i = 0; i < len; ++i) {
    count += (ptr1[i] != ptr2[i]);
  }
  
  return count;
}

} // namespace hamming