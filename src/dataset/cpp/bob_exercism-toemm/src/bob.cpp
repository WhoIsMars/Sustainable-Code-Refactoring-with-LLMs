#include "bob.h"

namespace bob {

using namespace std;

const string hey(const string& msg) {

    bool allupper = true;
    bool is_question = ends_in_question(msg);
    bool only_whitespaces = true;
    int ctr{};

    for (const auto& ch : msg) {

        if (isalpha(ch)) {
            if (islower(ch)) allupper = false;
            ctr++;
        }
        if (isspace(ch) == false) only_whitespaces = false;
    }

    if (only_whitespaces == true) return "Fine. Be that way!";

    if (is_question == true) {
        if (allupper == true && ctr) return "Calm down, I know what I'm doing!";
        else return "Sure.";
    } else if (allupper == true && ctr) return "Whoa, chill out!";

    return "Whatever.";
}

template<typename T>
bool ends_in_question(const T& msg) {

    for (auto it = msg.rbegin(); it != msg.rend(); it++) {

        if (isspace(*it) == false) {
            if (*it == '?') return true;
            else return false;
        }
    }

    return false;
}

}  // namespace bob
