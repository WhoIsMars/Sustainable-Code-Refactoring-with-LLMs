#include "bob.h"
#include <algorithm>
#include <cctype>

namespace bob {

using namespace std;

const string hey(const string& msg) {
    bool all_upper = false;
    bool has_letters = false;
    bool is_question = false;
    bool non_space_found = false;

    for (auto it = msg.rbegin(); it != msg.rend(); ++it) {
        if (!isspace(*it)) {
            non_space_found = true;
            if (*it == '?') {
                is_question = true;
            }
            break;
        }
    }

    if (!non_space_found) {
        return "Fine. Be that way!";
    }

    for (char ch : msg) {
        if (isalpha(ch)) {
            has_letters = true;
            if (islower(ch)) {
                all_upper = false;
                break;
            }
            all_upper = true;
        } else if (!isspace(ch) && !isalnum(ch)) {
            all_upper = false;
        }
    }

    if (is_question) {
        if (all_upper && has_letters) {
            return "Calm down, I know what I'm doing!";
        } else {
            return "Sure.";
        }
    } else if (all_upper && has_letters) {
        return "Whoa, chill out!";
    }

    return "Whatever.";
}

}  // namespace bob