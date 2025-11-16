#include "matching_brackets.h"

#include <string>

namespace matching_brackets {

bool check(const std::string& text) {
    std::string braces;

    for (char ch : text) {
        switch (ch) {
            case '(':
            case '[':
            case '{':
                braces.push_back(ch);
                break;
            case ')':
                if (braces.empty() || braces.back() != '(') return false;
                braces.pop_back();
                break;
            case ']':
                if (braces.empty() || braces.back() != '[') return false;
                braces.pop_back();
                break;
            case '}':
                if (braces.empty() || braces.back() != '{') return false;
                braces.pop_back();
                break;
        }
    }

    return braces.empty();
}

}  // namespace matching_brackets