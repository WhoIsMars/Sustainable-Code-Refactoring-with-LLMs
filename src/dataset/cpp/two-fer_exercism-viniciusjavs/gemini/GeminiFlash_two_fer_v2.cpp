#include "two_fer.h"

namespace two_fer {

string two_fer(const string& name) {
  return "One for " + (name.empty() ? "you" : name) + ", one for me.";
}

} // namespace two_fer