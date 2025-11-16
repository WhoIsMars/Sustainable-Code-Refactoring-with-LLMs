#include "bracket_push.h"

#include <stack>
#include <unordered_map>
#include <string>

using std::stack;
using std::string;
using std::unordered_map;

bool bracket_push::check(string phrase) {
    static const unordered_map<char, char> bracket_pairs = {
        {')', '('}, {']', '['}, {'}', '{'}
    };
    stack<char> open_brackets;

    for (char c : phrase) {
        if (bracket_pairs.count(c)) {
            if (open_brackets.empty() || open_brackets.top() != bracket_pairs.at(c)) {
                return false;
            }
            open_brackets.pop();
        } else if (bracket_pairs.contains_value(c)) {
            open_brackets.push(c);
        }
    }
    return open_brackets.empty();
}