#include "bob.h"
#include <string>
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
        int l = input.length();
        for (int i = l - 1; i >= 0; i--)
        {
            if (input[i] == ' ' || input[i] == '\t')
                continue;
            else if (input[i] == '?')
                return true;
            else
                return false;
        }
        return false;
    }
    bool isYelling(string input)
    {
        bool hasLetters = false;
        for (int i = 0; i < static_cast<int>(input.length()); i++)
            if (isalpha(input[i]))
            {
                hasLetters = true;
                if (islower(input[i]))
                    return false;
            }
        return hasLetters;
    }
    bool isSilence(string input)
    {
        for (int i = 0; i < static_cast<int>(input.length()); i++)
            if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n' || input[i] == '\r')
                continue;
            else
                return false;

        return true;
    }

} // namespace bob
