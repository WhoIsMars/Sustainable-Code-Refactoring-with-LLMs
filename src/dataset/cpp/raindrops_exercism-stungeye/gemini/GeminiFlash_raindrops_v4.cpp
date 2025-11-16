#include "raindrops.h"
#include <string>

namespace raindrops {

std::string convert(int number) {
  std::string raindrops;
  raindrops.reserve(16);

  if (number % 3 == 0) {
    raindrops.append("Pling");
  }

  if (number % 5 == 0) {
    raindrops.append("Plang");
  }

  if (number % 7 == 0) {
    raindrops.append("Plong");
  }

  if (raindrops.empty()) {
    return std::to_string(number);
  } else {
    return raindrops;
  }
}

} // namespace raindrops