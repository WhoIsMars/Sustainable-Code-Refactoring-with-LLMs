#include "two_fer.h"

namespace two_fer
{

  const std::string default_message = "One for you, one for me.";
  const std::string prefix = "One for ";
  const std::string suffix = ", one for me.";

  std::string two_fer() {
    return default_message;
  }

  std::string two_fer(const std::string& name) {
    return prefix + name + suffix;
  }
} // namespace two_fer