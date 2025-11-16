#include "matching_brackets.h"

#include <stack>

bool matching_brackets::check(std::string const &str) {
    std::stack<char> stack;
    stack.reserve(str.length() / 2 + 1);
    
    for (char ch : str) {
        if (ch == '[' || ch == '{' || ch == '(') {
            stack.push(bracket(ch));
        } else if (ch == ']' || ch == '}' || ch == ')') {
            if (stack.empty() || stack.top() != ch) 
                return false;
            stack.pop();
        }
    }
    return stack.empty();
}