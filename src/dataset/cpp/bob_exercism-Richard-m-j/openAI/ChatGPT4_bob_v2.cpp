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
        input.erase(input.begin(), find_if(input.begin(), input.end(), [](unsigned char ch) { return !isspace(ch); }));
        input.erase(find_if(input.rbegin(), input.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), input.end());

        if (input.empty())
            return "Fine. Be that way!";
        if (isYelling(input) && input.back() == '?')
            return "Calm down, I know what I'm doing!";
        if (isYelling(input))
            return "Whoa, chill out!";
        if (input.back() == '?')
            return "Sure.";
        return "Whatever.";
    }

    bool isYelling(const string &input)
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

} // namespace bob