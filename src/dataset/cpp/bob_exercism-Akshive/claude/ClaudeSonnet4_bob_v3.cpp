#include "bob.h"
#include <string>
#include <cctype>

using namespace std;

namespace bob {
    bool no_letter(const string& str) {
        for (char c : str) {
            if (isalpha(c)) return false;
        }
        return true;
    }

    bool is_all_capitals(const string& str) {
        bool has_letter = false;
        for (char c : str) {
            if (isalpha(c)) {
                has_letter = true;
                if (islower(c)) return false;
            }
        }
        return has_letter;
    }

    bool is_empty(const string& str) {
        for (char c : str) {
            if (!isspace(c)) return false;
        }
        return true;
    }

    bool is_question(const string& str) {
        for (int i = str.size() - 1; i >= 0; --i) {
            if (!isspace(str[i])) {
                return str[i] == '?';
            }
        }
        return false;
    }

    string hey(const string& str) {
        if (str.empty() || is_empty(str)) {
            return "Fine. Be that way!";
        }
        
        bool is_quest = is_question(str);
        bool is_caps = is_all_capitals(str);
        
        if (is_quest && is_caps) {
            return "Calm down, I know what I'm doing!";
        }
        if (is_quest) {
            return "Sure.";
        }
        if (is_caps) {
            return "Whoa, chill out!";
        }
        return "Whatever.";
    }
}