#include "bob.h"
#include <string>
#include <cctype>

namespace bob {
    bool no_letter(std::string str)
    {
        for (char c : str) {
            if (std::isalpha(c)) return false;
        }
        return true;
    }

    bool is_all_capitals(std::string str)
    {
        bool has_letter = false;
        for (char c : str) {
            if (std::isalpha(c)) {
                has_letter = true;
                if (std::islower(c)) return false;
            }
        }
        return has_letter;
    }

    bool is_empty(std::string str)
    {
        for (char c : str) {
            if (!std::isspace(c)) return false;
        }
        return true;
    }

    bool is_question(std::string str)
    {
        for (int i = str.size() - 1; i >= 0; --i) {
            if (!std::isspace(str[i])) {
                return str[i] == '?';
            }
        }
        return false;
    }

    std::string hey(std::string str) {
        if (str.empty() || is_empty(str)) return "Fine. Be that way!";
        
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