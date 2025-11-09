#include "bob.h"
#include <string>
#include <cctype>

namespace bob
{
    std::string hey(const std::string& input)
    {
        bool hasLetters = false;
        bool isAllUpper = true;
        bool isQuestionMark = false;
        bool hasNonWhitespace = false;
        
        // Single pass through the string
        for (size_t i = 0; i < input.length(); ++i)
        {
            char c = input[i];
            
            if (std::isalpha(c))
            {
                hasLetters = true;
                hasNonWhitespace = true;
                if (std::islower(c))
                {
                    isAllUpper = false;
                }
            }
            else if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
            {
                hasNonWhitespace = true;
            }
        }
        
        // Check for question mark at the end (ignoring trailing whitespace)
        for (int i = static_cast<int>(input.length()) - 1; i >= 0; --i)
        {
            char c = input[i];
            if (c == ' ' || c == '\t')
                continue;
            else if (c == '?')
            {
                isQuestionMark = true;
                break;
            }
            else
                break;
        }
        
        bool yelling = hasLetters && isAllUpper;
        bool question = isQuestionMark;
        bool silence = !hasNonWhitespace;
        
        if (yelling && question)
            return "Calm down, I know what I'm doing!";
        if (yelling)
            return "Whoa, chill out!";
        if (question)
            return "Sure.";
        if (silence)
            return "Fine. Be that way!";
        return "Whatever.";
    }
    
    bool isQuestion(const std::string& input)
    {
        for (int i = static_cast<int>(input.length()) - 1; i >= 0; --i)
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
    
    bool isYelling(const std::string& input)
    {
        bool hasLetters = false;
        for (size_t i = 0; i < input.length(); ++i)
        {
            char c = input[i];
            if (std::isalpha(c))
            {
                hasLetters = true;
                if (std::islower(c))
                    return false;
            }
        }
        return hasLetters;
    }
    
    bool isSilence(const std::string& input)
    {
        for (size_t i = 0; i < input.length(); ++i)
        {
            char c = input[i];
            if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
                return false;
        }
        return true;
    }
}