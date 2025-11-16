#include "matching_brackets.h"

#include <vector>

bool matching_brackets::check(std::string const& phrase) {
  std::vector<char> bracket;
  bracket.reserve(phrase.length() / 2);
  
  for (char c : phrase) {
    if (c == '(' || c == '[' || c == '{') {
      bracket.push_back(c);
    } else if (c == ')' || c == ']' || c == '}') {
      if (bracket.empty()) return false;
      char last = bracket.back();
      if ((c == ')' && last != '(') || 
          (c == ']' && last != '[') || 
          (c == '}' && last != '{')) {
        return false;
      }
      bracket.pop_back();
    }
  }
  return bracket.empty();
}