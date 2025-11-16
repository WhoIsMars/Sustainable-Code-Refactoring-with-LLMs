#include "matching_brackets.h"

#include <string>
#include <vector>
using namespace std;

namespace matching_brackets {
    bool check(std::string seq)
    {
        vector<char> st;
        st.reserve(seq.size() / 2 + 1);
        
        for(char c : seq)
        {
            switch(c) {
                case '(':
                case '{':
                case '[':
                    st.push_back(c);
                    break;
                case ')':
                    if(st.empty() || st.back() != '(') return false;
                    st.pop_back();
                    break;
                case '}':
                    if(st.empty() || st.back() != '{') return false;
                    st.pop_back();
                    break;
                case ']':
                    if(st.empty() || st.back() != '[') return false;
                    st.pop_back();
                    break;
            }
        }
        return st.empty();
    }

}  // namespace matching_brackets