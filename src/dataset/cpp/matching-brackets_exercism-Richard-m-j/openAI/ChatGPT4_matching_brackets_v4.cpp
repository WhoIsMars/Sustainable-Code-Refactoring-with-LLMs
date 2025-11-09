#include "matching_brackets.h"

namespace matching_brackets
{
    bool check(const string& s)
    {
        stack<char> stack;
        for (char ch : s)
        {
            switch (ch)
            {
                case '{': case '[': case '(':
                    stack.push(ch);
                    break;
                case '}':
                    if (stack.empty() || stack.top() != '{') return false;
                    stack.pop();
                    break;
                case ']':
                    if (stack.empty() || stack.top() != '[') return false;
                    stack.pop();
                    break;
                case ')':
                    if (stack.empty() || stack.top() != '(') return false;
                    stack.pop();
                    break;
            }
        }
        return stack.empty();
    }
} // namespace matching_brackets