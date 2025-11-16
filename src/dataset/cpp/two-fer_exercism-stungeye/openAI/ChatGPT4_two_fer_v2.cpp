#include "two_fer.h"

namespace two_fer
{

  const std::string default_message = "One for you, one for me.";

  std::string two_fer() {
    return default_message;
  }

  std::string two_fer(const std::string& name) {
    return "One for " + name + ", one for me.";
  }
} // namespace two_fer