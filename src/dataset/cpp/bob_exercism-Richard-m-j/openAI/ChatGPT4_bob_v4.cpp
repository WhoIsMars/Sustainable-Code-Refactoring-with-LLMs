#include "bob.h"
#include <string>
#include <cctype>
using namespace std;

namespace bob
{
    string hey(const string& input)
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

    bool isQuestion(const string& input)
    {
        for (auto it = input.rbegin(); it != input.rend(); ++it)
        {
            if (isspace(*it))
                continue;
            return *it == '?';
        }
        return false;
    }

    bool isYelling(const string& input)
    {
        bool hasLetters = false;
        for (char ch : input)
        {
            if (isalpha(ch))
            {
                hasLetters = true;
                if (islower(ch))
                    return false;
            }
        }
        return hasLetters;
    }

    bool isSilence(const string& input)
    {
        return all_of(input.begin(), input.end(), [](char ch) { return isspace(ch); });
    }

} // namespace bob