#include "matching_brackets.h"

#include <stack>

bool matching_brackets::check(std::string const &str) {
    std::stack<char> stack;
    stack.reserve(str.length() / 2 + 1);
    
    for (char ch : str) {
        if (ch == '[' || ch == '{' || ch == '(') {
            stack.push(ch);
        } else if (ch == ']' || ch == '}' || ch == ')') {
            if (stack.empty()) return false;
            
            char top = stack.top();
            stack.pop();
            
            if ((ch == ']' && top != '[') ||
                (ch == '}' && top != '{') ||
                (ch == ')' && top != '(')) {
                return false;
            }
        }
    }
    return stack.empty();
}