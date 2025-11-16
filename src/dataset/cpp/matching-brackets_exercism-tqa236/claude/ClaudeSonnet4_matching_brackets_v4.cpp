#include "matching_brackets.h"

#include <vector>

bool matching_brackets::check(std::string const& phrase) {
  std::vector<char> bracket;
  bracket.reserve(phrase.size() / 2);
  
  for (char c : phrase) {
    switch (c) {
      case '(':
      case '[':
      case '{':
        bracket.push_back(c);
        break;
      case ')':
        if (bracket.empty() || bracket.back() != '(') return false;
        bracket.pop_back();
        break;
      case ']':
        if (bracket.empty() || bracket.back() != '[') return false;
        bracket.pop_back();
        break;
      case '}':
        if (bracket.empty() || bracket.back() != '{') return false;
        bracket.pop_back();
        break;
    }
  }
  return bracket.empty();
}