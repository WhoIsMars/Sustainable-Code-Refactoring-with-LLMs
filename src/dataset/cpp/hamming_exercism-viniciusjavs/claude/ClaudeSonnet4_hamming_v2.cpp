#include "hamming.h"

namespace hamming {

int compute(string const &first, string const &second) {
  if (first.length() != second.length())
    throw std::domain_error{"Sequences differ in length."};

  int count = 0;
  const char* p1 = first.data();
  const char* p2 = second.data();
  const char* end = p1 + first.length();
  
  while (p1 != end) {
    count += (*p1++ != *p2++);
  }
  
  return count;
}

} // namespace hamming