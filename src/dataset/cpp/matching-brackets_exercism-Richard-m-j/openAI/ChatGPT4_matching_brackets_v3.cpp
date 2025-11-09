#include "matching_brackets.h"

namespace matching_brackets
{
    bool check(string s)
    {
        stack<char> stack;
        for (char c : s)
        {
            if (c == '{' || c == '[' || c == '(')
            {
                stack.push(c);
            }
            else if (c == '}' || c == ']' || c == ')')
            {
                if (stack.empty() || 
                    (c == '}' && stack.top() != '{') || 
                    (c == ']' && stack.top() != '[') || 
                    (c == ')' && stack.top() != '('))
                {
                    return false;
                }
                stack.pop();
            }
        }
        return stack.empty();
    }
} // namespace matching_brackets