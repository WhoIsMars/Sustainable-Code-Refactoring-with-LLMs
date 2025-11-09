#include "bob.h"
#include <string>
using namespace std;
namespace bob
{
    string hey(const string& input)
    {
        bool hasLetters = false;
        bool isAllUpper = true;
        bool isQuestionMark = false;
        bool hasNonWhitespace = false;
        
        // Single pass through the string
        int len = input.length();
        for (int i = 0; i < len; i++)
        {
            char c = input[i];
            
            if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
            {
                hasNonWhitespace = true;
            }
            
            if (isalpha(c))
            {
                hasLetters = true;
                if (islower(c))
                {
                    isAllUpper = false;
                }
            }
        }
        
        // Check for question mark from the end
        for (int i = len - 1; i >= 0; i--)
        {
            char c = input[i];
            if (c != ' ' && c != '\t')
            {
                isQuestionMark = (c == '?');
                break;
            }
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
    
    bool isQuestion(const string& input)
    {
        int l = input.length();
        for (int i = l - 1; i >= 0; i--)
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
        int len = input.length();
        for (int i = 0; i < len; i++)
        {
            char c = input[i];
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
        int len = input.length();
        for (int i = 0; i < len; i++)
        {
            char c = input[i];
            if (c != ' ' && c != '\t' && c != '\n' && c != '\r')
                return false;
        }
        return true;
    }

} // namespace bob