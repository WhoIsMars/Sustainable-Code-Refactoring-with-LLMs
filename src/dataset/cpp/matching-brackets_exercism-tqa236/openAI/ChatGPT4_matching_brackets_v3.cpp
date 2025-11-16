#include "matching_brackets.h"

#include <unordered_map>
#include <string>

bool matching_brackets::check(std::string const& phrase) {
  std::string stack;
  static const std::unordered_map<char, char> brackets = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
  for (char c : phrase) {
    if (brackets.count(c)) {
      stack.push_back(c);
    } else if (!stack.empty() && c == brackets.at(stack.back())) {
      stack.pop_back();
    } else if (c == ')' || c == ']' || c == '}') {
      return false;
    }
  }
  return stack.empty();
}