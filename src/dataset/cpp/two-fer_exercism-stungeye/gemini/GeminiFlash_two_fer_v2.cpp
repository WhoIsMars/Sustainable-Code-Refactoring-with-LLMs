#include "two_fer.h"
#include <string>

namespace two_fer
{

  std::string two_fer() {
    return "One for you, one for me.";
  }

  std::string two_fer(const std::string& name) {
    std::string result = "One for ";
    result.reserve(18 + name.length());
    result += name;
    result += ", one for me.";
    return result;
  }
} // namespace two_fer