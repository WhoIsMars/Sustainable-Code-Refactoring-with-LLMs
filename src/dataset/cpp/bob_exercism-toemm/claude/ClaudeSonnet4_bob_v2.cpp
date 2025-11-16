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
    bool only_whitespaces = true;
    int ctr = 0;

    for (const auto& ch : msg) {
        if (isalpha(ch)) {
            if (islower(ch)) allupper = false;
            ++ctr;
        }
        if (!isspace(ch)) only_whitespaces = false;
    }

    if (only_whitespaces) return "Fine. Be that way!";

    bool is_question = ends_in_question(msg);
    
    if (is_question) {
        return (allupper && ctr) ? "Calm down, I know what I'm doing!" : "Sure.";
    } else if (allupper && ctr) {
        return "Whoa, chill out!";
    }

    return "Whatever.";
}

}  // namespace bob