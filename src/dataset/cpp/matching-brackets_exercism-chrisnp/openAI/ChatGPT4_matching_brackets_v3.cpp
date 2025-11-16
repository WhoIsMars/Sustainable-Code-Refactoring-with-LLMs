#include "matching_brackets.h"

#include <stack>
#include <unordered_map>

bool matching_brackets::check(std::string const &str) {
    static const std::unordered_map<char, char> bracket_pairs = {
        {')', '('}, {'}', '{'}, {']', '['}
    };
    std::stack<char> stack;
    for (char ch : str) {
        if (bracket_pairs.count(ch)) {
            if (stack.empty() || stack.top() != bracket_pairs.at(ch)) 
                return false;
            stack.pop();
        } else if (ch == '(' || ch == '{' || ch == '[') {
            stack.push(ch);
        }
    }
    return stack.empty();
}