#include "matching_brackets.h"

namespace matching_brackets {

bool check(const std::string& text) {
    const char* ptr = text.data();
    const char* end = ptr + text.size();
    
    char stack_buffer[256];
    char* stack_top = stack_buffer;
    
    while (ptr < end) {
        char ch = *ptr++;
        
        if (ch == '(' || ch == '[' || ch == '{') {
            *stack_top++ = ch;
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (stack_top == stack_buffer) return false;
            
            char last = *--stack_top;
            if ((last == '(' && ch != ')') ||
                (last == '[' && ch != ']') ||
                (last == '{' && ch != '}')) {
                return false;
            }
        }
    }
    
    return stack_top == stack_buffer;
}

}  // namespace matching_brackets