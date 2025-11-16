#include "matching_brackets.h"

#include <stack>

namespace matching_brackets {

using namespace std;


bool check(const std::string& text) {

    stack<char> braces;

    for (auto ch : text) {

        switch (ch)
        {
        case '(':
        case '[':
        case '{':
            braces.push(ch);
            continue;
  
        case ')':
        case ']':
        case '}':
            // if ending braces occurs before opening braces, return flase
            if (braces.empty()) return false;

            // check latest
            auto last = braces.top();

            // ASCII magic check if nesting is correct
            // last+1 (for round braces), and last+2 for curly and square braces
            if (last+1 != ch && last+2 != ch) return false;  // nesting error 
            else braces.pop(); // nesting correct
            continue;
        }
    }

    return braces.empty();

}

}  // namespace matching_brackets
