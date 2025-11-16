#include "matching_brackets.h"

#include <stack>

namespace matching_brackets {

bool check(const std::string& text) {
    std::stack<char> braces;
    
    for (char ch : text) {
        if (ch == '(' || ch == '[' || ch == '{') {
            braces.push(ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (braces.empty()) return false;
            
            char last = braces.top();
            braces.pop();
            
            if ((last == '(' && ch != ')') ||
                (last == '[' && ch != ']') ||
                (last == '{' && ch != '}')) {
                return false;
            }
        }
    }
    
    return braces.empty();
}

}  // namespace matching_brackets