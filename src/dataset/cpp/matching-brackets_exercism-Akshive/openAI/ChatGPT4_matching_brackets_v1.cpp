#include "matching_brackets.h"

#include <string>
using namespace std;

namespace matching_brackets {
    bool check(std::string seq)
    {
        string st;
        for(char ch : seq)
        {
            if(ch == '(' || ch == '{' || ch == '[') {
                st.push_back(ch);
            } else {
                if(st.empty() || 
                   (ch == ')' && st.back() != '(') || 
                   (ch == '}' && st.back() != '{') || 
                   (ch == ']' && st.back() != '[')) {
                    return false;
                }
                st.pop_back();
            }
        }
        return st.empty();
    }

}  // namespace matching_brackets