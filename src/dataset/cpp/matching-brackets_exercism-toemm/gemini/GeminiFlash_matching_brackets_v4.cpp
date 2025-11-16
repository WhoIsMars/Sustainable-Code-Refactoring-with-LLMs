#include "matching_brackets.h"

#include <stack>
#include <string_view>

namespace matching_brackets {

bool check(const std::string& text) {
    std::stack<char> braces;
    for (const char ch : text) {
        switch (ch) {
            case '(':
            case '[':
            case '{':
                braces.push(ch);
                break;
            case ')':
                if (braces.empty() || braces.top() != '(') return false;
                braces.pop();
                break;
            case ']':
                if (braces.empty() || braces.top() != '[') return false;
                braces.pop();
                break;
            case '}':
                if (braces.empty() || braces.top() != '{') return false;
                braces.pop();
                break;
            default:
                break;
        }
    }
    return braces.empty();
}

}  // namespace matching_brackets