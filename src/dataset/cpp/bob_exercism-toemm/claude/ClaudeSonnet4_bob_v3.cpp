#include "bob.h"

namespace bob {

using namespace std;

template<typename T>
bool ends_in_question(const T& msg) {
    for (auto it = msg.rbegin(); it != msg.rend(); ++it) {
        if (!isspace(*it)) {
            return *it == '?';
        }
    }
    return false;
}

const string hey(const string& msg) {
    bool allupper = true;
    bool has_letters = false;
    bool only_whitespaces = true;
    
    for (const auto& ch : msg) {
        if (!isspace(ch)) {
            only_whitespaces = false;
        }
        
        if (isalpha(ch)) {
            has_letters = true;
            if (islower(ch)) {
                allupper = false;
            }
        }
    }

    if (only_whitespaces) {
        return "Fine. Be that way!";
    }

    bool is_question = ends_in_question(msg);
    bool is_yelling = allupper && has_letters;

    if (is_question && is_yelling) {
        return "Calm down, I know what I'm doing!";
    }
    if (is_question) {
        return "Sure.";
    }
    if (is_yelling) {
        return "Whoa, chill out!";
    }

    return "Whatever.";
}

}  // namespace bob