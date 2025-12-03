#include "reverse_string.h"
#include <string>
#include <algorithm>

using namespace std;

namespace reverse_string {

string reverse_string(string input) {
  std::reverse(input.begin(), input.end());
  return input;
}

} // namespace reverse_string