#include "matching_brackets.h"

namespace matching_brackets
{
    bool check(string s)
    {
        stack<char> stack;
        int n = s.length();
        for (int i = 0; i < n; i++)
            if (s[i] == '{' || s[i] == '[' || s[i] == '(')
                stack.push(s[i]);
            else if (s[i] == '}')
            {
                if (stack.empty())
                    return false;
                if (stack.top() != '{')
                    return false;
                else
                    stack.pop();
            }
            else if (s[i] == ']')
            {
                if (stack.empty())
                    return false;
                if (stack.top() != '[')
                    return false;
                else
                    stack.pop();
            }
            else if (s[i] == ')')
            {
                if (stack.empty())
                    return false;
                if (stack.top() != '(')
                    return false;
                else
                    stack.pop();
            }

        if (stack.empty())
            return true;
        else
            return false;
    }
} // namespace matching_brackets
