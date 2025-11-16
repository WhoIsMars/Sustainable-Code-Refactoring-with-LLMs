#include "bob.h"

namespace {

    char get_last_nonspace_char(const std::string& input)
    {
        for (ssize_t ndx = input.length()-1; ndx >= 0; --ndx) {
            if (input[ndx] != ' ')
                return input[ndx];
        }

        return ' ';
    }

    // last non-space character is a question-mark
    bool is_question(char last_char)
    {
        return last_char == '?';
    }

    // Any letters must be capitalized, and there must be at least one letter
    bool is_shouting(const std::string& input)
    {
        bool cap_letter_detected(false);

        for (auto c : input) {
            if (c >= 'a' && c <= 'z')
                return false;
            else if (!cap_letter_detected && c >= 'A' && c <= 'Z')
                cap_letter_detected = true;
        }
        
        return cap_letter_detected;
    }

    // 0 or more spaces
    bool is_silence(const std::string& input)
    {
        for (auto c : input) {
            if (c != ' ')
                return false;
        }

        return true;
    }
};

std::string
bob::hey(const std::string& input)
{
    const char last_char = get_last_nonspace_char(input);

    if (is_silence(input))
        return "Fine. Be that way!";
    else if (is_shouting(input))
        return "Whoa, chill out!";
    else if (is_question(last_char))
        return "Sure.";

    return "Whatever.";
}
