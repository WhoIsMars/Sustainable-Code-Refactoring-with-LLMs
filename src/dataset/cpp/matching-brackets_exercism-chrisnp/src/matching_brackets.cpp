#include "matching_brackets.h"

#include <stack>

bool matching_brackets::check(std::string const &str) {
    std::stack<char> stack {};
    for (auto ch : str) {
        switch (ch) {
            case '[':
            case '{':
            case '(':
                stack.push(bracket(ch));
                break;
            case ']':
            case '}':
            case ')':
                if (stack.size() == 0 || stack.top() != ch) 
                    return false;
                stack.pop();
            default: continue;
        }
    }
    return stack.empty();
}
