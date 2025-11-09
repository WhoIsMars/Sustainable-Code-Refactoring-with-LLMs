#include "bob.h"
#include <string>
#include <cctype>
using namespace std;

namespace bob
{
    string hey(const string& input)
    {
        bool hasLetters = false;
        bool isYell = true;
        bool isQuest = false;
        bool hasPrintable = false;
        
        // Single pass through the string
        for (int i = 0; i < static_cast<int>(input.length()); i++)
        {
            char c = input[i];
            
            if (isalpha(c))
            {
                hasLetters = true;
                if (islower(c))
                    isYell = false;
            }
            else if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
            {
                hasPrintable = true;
            }
        }
        
        // Check for question mark at the end (skip trailing whitespace)
        for (int i = input.length() - 1; i >= 0; i--)
        {
            char c = input[i];
            if (c == ' ' || c == '\t')
                continue;
            else if (c == '?')
            {
                isQuest = true;
                break;
            }
            else
                break;
        }
        
        bool yelling = hasLetters && isYell;
        bool silence = !hasLetters && !hasPrintable;
        
        if (yelling && isQuest)
            return "Calm down, I know what I'm doing!";
        if (yelling)
            return "Whoa, chill out!";
        if (isQuest)
            return "Sure.";
        if (silence)
            return "Fine. Be that way!";
        return "Whatever.";
    }
    
    bool isQuestion(const string& input)
    {
        for (int i = input.length() - 1; i >= 0; i--)
        {
            char c = input[i];
            if (c == ' ' || c == '\t')
                continue;
            else if (c == '?')
                return true;
            else
                return false;
        }
        return false;
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
        for (char c : input)
        {
            if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
                return false;
        }
        return true;
    }

} // namespace bob