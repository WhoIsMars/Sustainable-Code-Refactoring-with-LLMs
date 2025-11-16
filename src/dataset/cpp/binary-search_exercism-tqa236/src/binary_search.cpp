#include "binary_search.h"

#include <algorithm>
#include <stdexcept>

using std::domain_error;

namespace binary_search {

size_t find(vector<int> data, int number) {
  auto it = std::find(data.begin(), data.end(), number);
  if (it != data.end()) {
    return it - data.begin();
  } else {
    throw domain_error("This number is not existed in the vector.");
  }
}

}  // namespace binary_search
