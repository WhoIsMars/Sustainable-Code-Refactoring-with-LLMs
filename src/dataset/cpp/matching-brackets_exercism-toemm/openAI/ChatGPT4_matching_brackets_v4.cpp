#include "matching_brackets.h"

#include <string>

namespace matching_brackets {

bool check(const std::string& text) {
    char stack[256];
    int top = -1;

    for (char ch : text) {
        switch (ch) {
            case '(':
            case '[':
            case '{':
                if (top == 255) return false; // Prevent stack overflow
                stack[++top] = ch;
                break;

            case ')':
                if (top < 0 || stack[top--] != '(') return false;
                break;

            case ']':
                if (top < 0 || stack[top--] != '[') return false;
                break;

            case '}':
                if (top < 0 || stack[top--] != '{') return false;
                break;
        }
    }

    return top == -1;
}

}  // namespace matching_brackets