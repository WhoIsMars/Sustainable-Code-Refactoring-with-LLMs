#include "two_fer.h"

namespace two_fer
{
  std::string two_fer() {
    static const std::string result = "One for you, one for me.";
    return result;
  }

  std::string two_fer(const std::string& name) {
    std::string result;
    result.reserve(15 + name.size());
    result = "One for ";
    result += name;
    result += ", one for me.";
    return result;
  }
}