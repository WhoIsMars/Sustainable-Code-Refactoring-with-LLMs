#include "bob.h"

namespace bob {

using namespace std;

const string hey(const string& msg) {
    bool allupper = false;
    bool is_question = false;
    bool only_whitespaces = true;
    int ctr = 0;

    for (auto it = msg.rbegin(); it != msg.rend(); ++it) {
        if (!isspace(*it)) {
            only_whitespaces = false;
            if (*it == '?') is_question = true;
            break;
        }
    }

    for (const auto& ch : msg) {
        if (isalpha(ch)) {
            allupper = allupper || isupper(ch);
            if (islower(ch)) allupper = false;
            ctr++;
        }
    }

    if (only_whitespaces) return "Fine. Be that way!";
    if (is_question) {
        if (allupper && ctr > 0) return "Calm down, I know what I'm doing!";
        return "Sure.";
    }
    if (allupper && ctr > 0) return "Whoa, chill out!";
    return "Whatever.";
}

}  // namespace bob