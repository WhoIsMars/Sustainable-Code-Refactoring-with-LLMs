#include "bracket_push.h"

#include <stack>
#include <unordered_map>
#include <string>

using std::stack;
using std::string;
using std::unordered_map;

bool bracket_push::check(string phrase) {
  unordered_map<char, char> matching_brackets = {{')', '('}, {']', '['}, {'}', '{'}};
  stack<char> open_brackets;

  for (char c : phrase) {
    if (matching_brackets.count(c)) {
      if (open_brackets.empty() || open_brackets.top() != matching_brackets[c]) {
        return false;
      }
      open_brackets.pop();
    } else if (matching_brackets.contains_value(c)) {
      open_brackets.push(c);
    }
  }

  return open_brackets.empty();
}