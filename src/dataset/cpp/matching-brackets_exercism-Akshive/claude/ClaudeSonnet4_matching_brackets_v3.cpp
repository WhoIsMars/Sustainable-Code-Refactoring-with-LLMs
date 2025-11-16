#include "matching_brackets.h"

#include <string>
#include <stack>

namespace matching_brackets {
    bool check(std::string seq)
    {
        std::stack<char> st;
        st.reserve(seq.size() / 2 + 1);
        
        for (char c : seq) {
            switch (c) {
                case '(':
                case '{':
                case '[':
                    st.push(c);
                    break;
                case ')':
                    if (st.empty() || st.top() != '(') return false;
                    st.pop();
                    break;
                case '}':
                    if (st.empty() || st.top() != '{') return false;
                    st.pop();
                    break;
                case ']':
                    if (st.empty() || st.top() != '[') return false;
                    st.pop();
                    break;
            }
        }
        return st.empty();
    }
}