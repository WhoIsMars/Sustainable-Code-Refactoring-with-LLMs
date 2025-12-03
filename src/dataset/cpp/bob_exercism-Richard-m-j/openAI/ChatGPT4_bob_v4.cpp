#include "bob.h"
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

namespace bob
{
    string hey(string input)
    {
        input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
        if (input.empty())
            return "Fine. Be that way!";
        bool yelling = isYelling(input);
        bool question = input.back() == '?';
        if (yelling && question)
            return "Calm down, I know what I'm doing!";
        if (yelling)
            return "Whoa, chill out!";
        if (question)
            return "Sure.";
        return "Whatever.";
    }

    bool isYelling(const string &input)
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
} // namespace bob