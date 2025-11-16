#include "bob.h"
#include <algorithm>
#include <cctype>

namespace bob {

using namespace std;

const string hey(const string& msg) {
    bool allupper = true;
    bool is_question = false;
    bool has_letters = false;
    bool only_whitespaces = true;

    for (size_t i = 0; i < msg.length(); ++i) {
        if (!isspace(msg[i])) {
            only_whitespaces = false;
            if (msg[i] == '?') {
                is_question = (i == msg.length() - 1);
                size_t j = i - 1;
                while (j >= 0 && isspace(msg[j])) {
                    j--;
                    if (j < 0) {
                        is_question = true;
                        break;
                    }
                }
                if (j >= 0 && !isspace(msg[j])) {
                    is_question = (msg[j] == '?');
                }
            }
        }
    }

    if (only_whitespaces) return "Fine. Be that way!";

    for (const auto& ch : msg) {
        if (isalpha(ch)) {
            has_letters = true;
            if (islower(ch)) {
                allupper = false;
                break;
            }
        }
    }

    if (is_question) {
        if (allupper && has_letters) return "Calm down, I know what I'm doing!";
        else return "Sure.";
    } else if (allupper && has_letters) return "Whoa, chill out!";

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