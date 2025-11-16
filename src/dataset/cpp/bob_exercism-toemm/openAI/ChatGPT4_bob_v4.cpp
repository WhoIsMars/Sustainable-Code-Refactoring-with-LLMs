#include "bob.h"

namespace bob {

using namespace std;

const string hey(const string& msg) {
    bool all_upper = true;
    bool is_question = false;
    bool only_whitespaces = true;
    int alpha_count = 0;

    for (auto it = msg.rbegin(); it != msg.rend(); ++it) {
        if (!isspace(*it)) {
            only_whitespaces = false;
            if (*it == '?') is_question = true;
            else is_question = false;
            break;
        }
    }

    for (const char ch : msg) {
        if (isalpha(ch)) {
            if (islower(ch)) all_upper = false;
            ++alpha_count;
        } else if (!isspace(ch)) {
            all_upper = false;
        }
    }

    if (only_whitespaces) return "Fine. Be that way!";
    if (is_question) {
        if (all_upper && alpha_count > 0) return "Calm down, I know what I'm doing!";
        return "Sure.";
    }
    if (all_upper && alpha_count > 0) return "Whoa, chill out!";
    return "Whatever.";
}

}  // namespace bob