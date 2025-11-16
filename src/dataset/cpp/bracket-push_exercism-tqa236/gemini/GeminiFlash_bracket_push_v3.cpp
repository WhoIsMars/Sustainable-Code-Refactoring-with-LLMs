#include "bracket_push.h"

#include <stack>
#include <string>

using std::stack;
using std::string;

bool bracket_push::check(string phrase) {
  stack<char> s;
  for (char c : phrase) {
    if (c == '(' || c == '[' || c == '{') {
      s.push(c);
    } else if (c == ')' || c == ']' || c == '}') {
      if (s.empty()) {
        return false;
      }
      char top = s.top();
      s.pop();
      if ((c == ')' && top != '(') || (c == ']' && top != '[') ||
          (c == '}' && top != '{')) {
        return false;
      }
    }
  }
  return s.empty();
}