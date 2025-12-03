#include "raindrops.h"
#include <string>

namespace raindrops {

std::string convert(int number) {
  std::string result;
  result.reserve(20);

  if (number % 3 == 0) {
    result += "Pling";
  }
  if (number % 5 == 0) {
    result += "Plang";
  }
  if (number % 7 == 0) {
    result += "Plong";
  }

  if (result.empty()) {
    return std::to_string(number);
  }

  return result;
}

} // namespace raindrops