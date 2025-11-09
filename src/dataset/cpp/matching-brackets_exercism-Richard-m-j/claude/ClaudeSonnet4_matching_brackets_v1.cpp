#include "matching_brackets.h"

namespace matching_brackets
{
    bool check(string s)
    {
        stack<char> stack;
        stack.reserve(s.length() / 2 + 1);
        
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
            }
        }
        
        return stack.empty();
    }
} // namespace matching_brackets