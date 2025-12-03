#include "reverse_string.h"
#include <string>
#include <algorithm>

namespace reverse_string {

std::string reverse_string(std::string sentence) {
  std::reverse(sentence.begin(), sentence.end());
  return sentence;
}

}