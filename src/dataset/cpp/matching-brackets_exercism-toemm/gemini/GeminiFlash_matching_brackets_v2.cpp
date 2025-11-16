#include "matching_brackets.h"

#include <stack>
#include <string_view>

namespace matching_brackets {

using namespace std;

bool check(const std::string& text) {
    stack<char> braces;
    for (const char ch : text) {
        if (ch == '(' || ch == '[' || ch == '{') {
            braces.push(ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (braces.empty()) {
                return false;
            }
            char last = braces.top();
            braces.pop();
            if ((ch == ')' && last != '(') ||
                (ch == ']' && last != '[') ||
                (ch == '}' && last != '{')) {
                return false;
            }
        }
    }
    return braces.empty();
}

}  // namespace matching_brackets