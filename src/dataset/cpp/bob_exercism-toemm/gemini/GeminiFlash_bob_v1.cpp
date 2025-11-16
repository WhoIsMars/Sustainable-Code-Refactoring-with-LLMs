#include "bob.h"
#include <algorithm>
#include <cctype>

namespace bob {

using namespace std;

const string hey(const string& msg) {
    bool all_upper = false;
    bool has_letters = false;
    bool is_question = false;
    bool only_whitespaces = true;

    for (size_t i = 0; i < msg.length(); ++i) {
        if (!isspace(msg[i])) {
            only_whitespaces = false;
            if (msg[i] == '?') {
                is_question = true;
            } else {
                is_question = false;
            }
        }
    }

    if (only_whitespaces) {
        return "Fine. Be that way!";
    }

    for (char c : msg) {
        if (isalpha(c)) {
            has_letters = true;
            if (islower(c)) {
                all_upper = false;
                break;
            } else {
                all_upper = true;
            }
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

template<typename T>
bool ends_in_question(const T& msg) {
    if (msg.empty()) return false;

    for (auto it = msg.rbegin(); it != msg.rend(); ++it) {
        if (!isspace(*it)) {
            return *it == '?';
        }
    }

    return false;
}

}  // namespace bob