#include "matching_brackets.h"

#include <unordered_map>
#include <string>

bool matching_brackets::check(std::string const& phrase) {
  std::string bracket_stack;
  const std::unordered_map<char, char> brackets = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
  
  for (char c : phrase) {
    if (brackets.count(c)) {
      bracket_stack.push_back(c);
    } else if (!bracket_stack.empty() && c == brackets.at(bracket_stack.back())) {
      bracket_stack.pop_back();
    } else if (c == ')' || c == ']' || c == '}') {
      return false;
    }
  }
  return bracket_stack.empty();
}