#include "bracket_push.h"

#include <stack>

using std::stack;
using std::string;

bool bracket_push::check(string phrase) {
  stack<char> bracket_stack;
  
  for (char c : phrase) {
    switch (c) {
      case '(':
      case '[':
      case '{':
        bracket_stack.push(c);
        break;
      case ')':
        if (bracket_stack.empty() || bracket_stack.top() != '(') return false;
        bracket_stack.pop();
        break;
      case ']':
        if (bracket_stack.empty() || bracket_stack.top() != '[') return false;
        bracket_stack.pop();
        break;
      case '}':
        if (bracket_stack.empty() || bracket_stack.top() != '{') return false;
        bracket_stack.pop();
        break;
    }
  }
  
  return bracket_stack.empty();
}