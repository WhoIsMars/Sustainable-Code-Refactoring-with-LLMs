#include "binary_search.h"

#include <algorithm>
#include <stdexcept>

using std::domain_error;

namespace binary_search {

size_t find(const vector<int>& data, int number) {
  auto it = std::lower_bound(data.begin(), data.end(), number);
  if (it != data.end() && *it == number) {
    return it - data.begin();
  } else {
    throw domain_error("This number is not existed in the vector.");
  }
}

}  // namespace binary_search