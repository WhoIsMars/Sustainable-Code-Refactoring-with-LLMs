#include "matching_brackets.h"
#include <stack>

namespace matching_brackets
{
    bool check(std::string s)
    {
        std::stack<char> stack;
        for (char c : s)
        {
            switch (c)
            {
            case '{':
            case '[':
            case '(':
                stack.push(c);
                break;
            case '}':
                if (stack.empty() || stack.top() != '{')
                    return false;
                stack.pop();
                break;
            case ']':
                if (stack.empty() || stack.top() != '[')
                    return false;
                stack.pop();
                break;
            case ')':
                if (stack.empty() || stack.top() != '(')
                    return false;
                stack.pop();
                break;
            default:
                break; // Ignore other characters
            }
        }
        return stack.empty();
    }
} // namespace matching_brackets