#include "matching_brackets.h"

#include <string>
#include <stack>
#include <unordered_map>

namespace matching_brackets {
    bool check(std::string seq) {
        std::stack<char> st;
        std::unordered_map<char, char> bracket_map = {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };

        for (char c : seq) {
            if (c == '(' || c == '{' || c == '[') {
                st.push(c);
            } else if (c == ')' || c == '}' || c == ']') {
                if (st.empty() || st.top() != bracket_map[c]) {
                    return false;
                }
                st.pop();
            }
        }

        return st.empty();
    }
}  // namespace matching_brackets