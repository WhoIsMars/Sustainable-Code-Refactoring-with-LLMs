#include "matching_brackets.h"

namespace matching_brackets {

bool check(const std::string& text) {
    char stack_buffer[256];
    int stack_top = -1;
    
    for (char ch : text) {
        if (ch == '(' || ch == '[' || ch == '{') {
            if (stack_top >= 255) return false; // overflow protection
            stack_buffer[++stack_top] = ch;
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (stack_top < 0) return false;
            
            char last = stack_buffer[stack_top--];
            if ((last == '(' && ch != ')') ||
                (last == '[' && ch != ']') ||
                (last == '{' && ch != '}')) {
                return false;
            }
        }
    }
    
    return stack_top == -1;
}

}  // namespace matching_brackets