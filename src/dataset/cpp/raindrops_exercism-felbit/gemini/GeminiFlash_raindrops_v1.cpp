#include "raindrops.h"
#include <string>

namespace raindrops {

std::string convert(int number) {
  std::string result;
  result.reserve(16); 

  bool converted = false;

  if (number % 3 == 0) {
    result += "Pling";
    converted = true;
  }
  if (number % 5 == 0) {
    result += "Plang";
    converted = true;
  }
  if (number % 7 == 0) {
    result += "Plong";
    converted = true;
  }

  if (!converted) {
    result = std::to_string(number);
  }

  return result;
}

}  // namespace raindrops