#include "binary.h"

#include <algorithm>
#include <stdexcept>

namespace binary {

int convert(const std::string& binary) {
  int decimal = 0;
  int power_of_two = 1;

  for (auto it = binary.rbegin(); it != binary.rend(); ++it) {
    const char bit = *it;

    if (bit == '1') {
      decimal += power_of_two;
    } else if (bit != '0') {
      return 0;
    }

    power_of_two *= 2;
  }

  return decimal;
}

} // namespace binary