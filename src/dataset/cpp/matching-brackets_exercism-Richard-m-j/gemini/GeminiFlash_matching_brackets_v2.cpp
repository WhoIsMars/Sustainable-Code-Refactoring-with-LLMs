#include "matching_brackets.h"

namespace matching_brackets {

bool check(const std::string& s) {
  std::stack<char> stack;
  for (char c : s) {
    switch (c) {
      case '{':
      case '[':
      case '(':
        stack.push(c);
        break;
      case '}':
        if (stack.empty() || stack.top() != '{') return false;
        stack.pop();
        break;
      case ']':
        if (stack.empty() || stack.top() != '[') return false;
        stack.pop();
        break;
      case ')':
        if (stack.empty() || stack.top() != '(') return false;
        stack.pop();
        break;
      default:
        // Ignore other characters
        break;
    }
  }
  return stack.empty();
}

} // namespace matching_brackets