#include "two_fer.h"
#include <string_view>

namespace two_fer {

string two_fer(std::string_view name) {
  return "One for " + std::string(name) + ", one for me.";
}

} // namespace two_fer