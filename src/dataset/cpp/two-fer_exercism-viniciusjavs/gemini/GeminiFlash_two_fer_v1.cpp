#include "two_fer.h"

namespace two_fer {

string two_fer(const string& name) {
  if (name.empty()) {
    return "One for you, one for me.";
  }
  return "One for " + name + ", one for me.";
}

} // namespace two_fer