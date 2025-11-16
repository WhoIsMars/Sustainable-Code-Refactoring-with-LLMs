#include "matching_brackets.h"

#include <string>
using namespace std;

namespace matching_brackets {
    bool check(const std::string& seq)
    {
        int count_paren = 0, count_brace = 0, count_bracket = 0;
        
        for(char c : seq)
        {
            switch(c) {
                case '(':
                    count_paren++;
                    break;
                case ')':
                    if(--count_paren < 0) return false;
                    break;
                case '{':
                    count_brace++;
                    break;
                case '}':
                    if(--count_brace < 0) return false;
                    break;
                case '[':
                    count_bracket++;
                    break;
                case ']':
                    if(--count_bracket < 0) return false;
                    break;
            }
        }
        
        return count_paren == 0 && count_brace == 0 && count_bracket == 0;
    }
}  // namespace matching_brackets