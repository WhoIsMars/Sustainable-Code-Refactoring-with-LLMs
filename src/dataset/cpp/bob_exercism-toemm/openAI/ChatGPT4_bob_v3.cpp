#include "bob.h"

namespace bob {

using namespace std;

const string hey(const string& msg) {
    bool allupper = false;
    bool is_question = false;
    bool only_whitespaces = true;
    int alpha_count = 0;

    for (auto it = msg.rbegin(); it != msg.rend(); ++it) {
        if (!isspace(*it)) {
            only_whitespaces = false;
            if (*it == '?') is_question = true;
            break;
        }
    }

    if (only_whitespaces) return "Fine. Be that way!";

    for (const auto& ch : msg) {
        if (isalpha(ch)) {
            alpha_count++;
            if (islower(ch)) {
                allupper = false;
                break;
            }
            allupper = true;
        }
    }

    if (is_question) {
        if (allupper && alpha_count) return "Calm down, I know what I'm doing!";
        return "Sure.";
    }

    if (allupper && alpha_count) return "Whoa, chill out!";

    return "Whatever.";
}

template<typename T>
bool ends_in_question(const T& msg) {
    for (auto it = msg.rbegin(); it != msg.rend(); ++it) {
        if (!isspace(*it)) return *it == '?';
    }
    return false;
}

}  // namespace bob