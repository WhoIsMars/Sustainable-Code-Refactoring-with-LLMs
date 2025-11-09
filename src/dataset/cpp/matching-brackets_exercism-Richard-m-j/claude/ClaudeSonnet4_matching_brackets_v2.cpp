#include "matching_brackets.h"

namespace matching_brackets
{
    bool check(string s)
    {
        stack<char> stack;
        for (char c : s)
        {
            if (c == '{' || c == '[' || c == '(')
                stack.push(c);
            else if (c == '}' || c == ']' || c == ')')
            {
                if (stack.empty())
                    return false;
                char top = stack.top();
                stack.pop();
                if ((c == '}' && top != '{') ||
                    (c == ']' && top != '[') ||
                    (c == ')' && top != '('))
                    return false;
            }
        }
        return stack.empty();
    }
} // namespace matching_brackets