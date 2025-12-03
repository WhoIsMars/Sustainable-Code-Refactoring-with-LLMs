#include "matching_brackets.h"

#include <string>
#include <stack>
#include <unordered_map>

namespace matching_brackets {
    bool check(std::string seq) {
        std::stack<char> st;
        std::unordered_map<char, char> matching_brackets = {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };

        for (char c : seq) {
            if (c == '(' || c == '{' || c == '[') {
                st.push(c);
            } else if (c == ')' || c == '}' || c == ']') {
                if (st.empty() || st.top() != matching_brackets[c]) {
                    return false;
                }
                st.pop();
            }
        }

        return st.empty();
    }
}  // namespace matching_brackets