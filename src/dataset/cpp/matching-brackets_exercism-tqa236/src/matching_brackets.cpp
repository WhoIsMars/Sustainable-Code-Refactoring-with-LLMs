#include "matching_brackets.h"

#include <map>
#include <vector>

bool matching_brackets::check(std::string const& phrase) {
  std::vector<char> bracket;
  std::map<char, char> brackets = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
  for (char c : phrase) {
    if (c == '(' || c == '[' || c == '{') {
      bracket.push_back(c);
    } else if (c == ')' || c == ']' || c == '}') {
      if (bracket.empty() || c != brackets[bracket.back()]) return false;
      bracket.pop_back();
    }
  }
  return bracket.empty();
}
