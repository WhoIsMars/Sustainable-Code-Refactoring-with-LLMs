#include "bob.h"
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

namespace bob
{
    string hey(string input)
    {
        // Trim whitespace from both ends
        input.erase(input.find_last_not_of(" \t\n\r") + 1);
        input.erase(0, input.find_first_not_of(" \t\n\r"));

        if (isSilence(input))
            return "Fine. Be that way!";
        if (isYelling(input) && isQuestion(input))
            return "Calm down, I know what I'm doing!";
        if (isYelling(input))
            return "Whoa, chill out!";
        if (isQuestion(input))
            return "Sure.";
        return "Whatever.";
    }

    bool isQuestion(const string& input)
    {
        return !input.empty() && input.back() == '?';
    }

    bool isYelling(const string& input)
    {
        bool hasLetters = false;
        for (char c : input)
        {
            if (isalpha(c))
            {
                hasLetters = true;
                if (islower(c))
                    return false;
            }
        }
        return hasLetters;
    }

    bool isSilence(const string& input)
    {
        return input.empty();
    }

} // namespace bob