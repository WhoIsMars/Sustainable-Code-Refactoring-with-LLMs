#include "bob.h"
#include <algorithm>
#include <cctype>

namespace bob {

using namespace std;

const string hey(const string& msg) {
    bool all_upper = true;
    bool is_question = false;
    bool has_letters = false;
    bool has_non_whitespace = false;

    for (auto it = msg.rbegin(); it != msg.rend(); ++it) {
        if (!isspace(*it)) {
            has_non_whitespace = true;
            if (*it == '?') {
                is_question = true;
            }
            break;
        }
    }

    if (!has_non_whitespace) {
        return "Fine. Be that way!";
    }

    for (const auto& ch : msg) {
        if (isalpha(ch)) {
            has_letters = true;
            if (islower(ch)) {
                all_upper = false;
                break;
            }
        }
    }

    bool is_all_upper_and_has_letters = all_upper && has_letters;

    if (is_question) {
        if (is_all_upper_and_has_letters) {
            return "Calm down, I know what I'm doing!";
        } else {
            return "Sure.";
        }
    } else if (is_all_upper_and_has_letters) {
        return "Whoa, chill out!";
    }

    return "Whatever.";
}

}  // namespace bob