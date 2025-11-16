#include "bob.h"

namespace bob {

using namespace std;

const string hey(const string& msg) {
    if (msg.empty()) return "Fine. Be that way!";
    
    bool allupper = false;
    bool has_alpha = false;
    bool only_whitespaces = true;
    bool is_question = false;
    
    auto it = msg.rbegin();
    const auto rend = msg.rend();
    
    while (it != rend && isspace(*it)) ++it;
    
    if (it != rend) {
        only_whitespaces = false;
        is_question = (*it == '?');
    }
    
    if (only_whitespaces) return "Fine. Be that way!";
    
    for (char ch : msg) {
        if (isalpha(ch)) {
            if (!has_alpha) {
                has_alpha = true;
                allupper = true;
            }
            if (islower(ch)) {
                allupper = false;
                break;
            }
        } else if (!isspace(ch)) {
            only_whitespaces = false;
        }
    }
    
    if (is_question) {
        return (allupper && has_alpha) ? "Calm down, I know what I'm doing!" : "Sure.";
    }
    
    return (allupper && has_alpha) ? "Whoa, chill out!" : "Whatever.";
}

template<typename T>
bool ends_in_question(const T& msg) {
    auto it = msg.rbegin();
    const auto rend = msg.rend();
    
    while (it != rend && isspace(*it)) ++it;
    
    return (it != rend && *it == '?');
}

}  // namespace bob