#include "reverse_string.h"
#include <algorithm>
#include <string>

namespace reverse_string {

std::string reverse_string(std::string sentence) {
  std::reverse(sentence.begin(), sentence.end());
  return sentence;
}

} // namespace reverse_string