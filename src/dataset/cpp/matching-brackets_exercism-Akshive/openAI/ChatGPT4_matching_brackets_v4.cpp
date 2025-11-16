#include "matching_brackets.h"

#include <string>
#include <stack>
using namespace std;

namespace matching_brackets {
    bool check(const std::string& seq)
    {
        stack<char> st;
        for(char ch : seq)
        {
            switch(ch)
            {
                case '(':
                case '{':
                case '[':
                    st.push(ch);
                    break;
                case ')':
                    if(st.empty() || st.top() != '(') return false;
                    st.pop();
                    break;
                case '}':
                    if(st.empty() || st.top() != '{') return false;
                    st.pop();
                    break;
                case ']':
                    if(st.empty() || st.top() != '[') return false;
                    st.pop();
                    break;
            }
        }
        return st.empty();
    }

}  // namespace matching_brackets