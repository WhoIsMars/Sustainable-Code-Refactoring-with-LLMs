#include "two_fer.h"
#include <string>
#include <string_view>

namespace two_fer
{

  std::string two_fer() {
    return "One for you, one for me.";
  }

  std::string two_fer(std::string_view name) {
    std::string result = "One for ";
    result.append(name);
    result.append(", one for me.");
    return result;
  }
} // namespace two_fer