#include <stdexcept>
#include "hamming.h"

using namespace std;

int hamming::compute(string a, string b) {
  if (a.length() != b.length()) {
    throw domain_error("a.size() != b.size()");
  }

  int result = 0;
  size_t length = a.length(); 

  for (size_t i = 0; i < length; ++i) {
    result += (a[i] != b[i]);
  }

  return result;
}