#include "bob.h"
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

namespace bob
{
    string hey(string input)
    {
        if (isYelling(input) && isQuestion(input))
            return "Calm down, I know what I'm doing!";
        if (isYelling(input))
            return "Whoa, chill out!";
        if (isQuestion(input))
            return "Sure.";
        if (isSilence(input))
            return "Fine. Be that way!";
        return "Whatever.";
    }

    bool isQuestion(string input)
    {
        auto it = find_if(input.rbegin(), input.rend(), [](char c) { return !isspace(c); });
        return it != input.rend() && *it == '?';
    }

    bool isYelling(string input)
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

    bool isSilence(string input)
    {
        return all_of(input.begin(), input.end(), [](char c) { return isspace(c); });
    }

} // namespace bob