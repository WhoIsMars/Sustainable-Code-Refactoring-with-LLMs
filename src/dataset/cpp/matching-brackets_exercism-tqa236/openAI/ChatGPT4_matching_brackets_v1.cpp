#include "matching_brackets.h"

#include <unordered_map>
#include <string>

bool matching_brackets::check(std::string const& phrase) {
  std::string bracket;
  static const std::unordered_map<char, char> brackets = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
  for (char c : phrase) {
    if (brackets.count(c)) {
      bracket.push_back(c);
    } else if (!bracket.empty() && c == brackets.at(bracket.back())) {
      bracket.pop_back();
    } else if (c == ')' || c == ']' || c == '}') {
      return false;
    }
  }
  return bracket.empty();
}