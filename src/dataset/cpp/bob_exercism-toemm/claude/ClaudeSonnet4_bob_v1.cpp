#include "bob.h"

namespace bob {

using namespace std;

const string hey(const string& msg) {
    if (msg.empty()) return "Fine. Be that way!";
    
    bool allupper = false;
    bool has_alpha = false;
    bool only_whitespaces = true;
    bool is_question = false;
    
    // Single pass through the string
    size_t last_non_space = string::npos;
    for (size_t i = 0; i < msg.size(); ++i) {
        const char ch = msg[i];
        
        if (!isspace(ch)) {
            only_whitespaces = false;
            last_non_space = i;
        }
        
        if (isalpha(ch)) {
            if (!has_alpha) {
                has_alpha = true;
                allupper = true;
            }
            if (islower(ch)) {
                allupper = false;
            }
        }
    }
    
    if (only_whitespaces) return "Fine. Be that way!";
    
    // Check if it's a question by looking at the last non-space character
    if (last_non_space != string::npos && msg[last_non_space] == '?') {
        is_question = true;
    }
    
    if (is_question) {
        if (allupper && has_alpha) return "Calm down, I know what I'm doing!";
        else return "Sure.";
    } else if (allupper && has_alpha) return "Whoa, chill out!";
    
    return "Whatever.";
}

template<typename T>
bool ends_in_question(const T& msg) {
    for (auto it = msg.rbegin(); it != msg.rend(); ++it) {
        if (!isspace(*it)) {
            return *it == '?';
        }
    }
    return false;
}

}  // namespace bob