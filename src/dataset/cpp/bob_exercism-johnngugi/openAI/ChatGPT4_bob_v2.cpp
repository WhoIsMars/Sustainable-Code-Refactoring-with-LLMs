#include "bob.h"
#include <string>
#include <cctype>
using namespace std;

string bob::hey(string statement)
{
    bool spaces_only = true;
    bool all_uppercase = true;
    bool has_question_mark = false;
    bool has_letters = false;

    for (auto it = statement.rbegin(); it != statement.rend(); ++it)
    {
        if (!isspace(*it))
        {
            spaces_only = false;
            if (*it == '?')
                has_question_mark = true;
            else
                has_question_mark = false;
        }

        if (isalpha(*it))
        {
            has_letters = true;
            if (!isupper(*it))
                all_uppercase = false;
        }

        if (!spaces_only && !all_uppercase && !has_question_mark)
            break;
    }

    if (spaces_only)
        return "Fine. Be that way!";
    if (all_uppercase && has_letters)
        return "Whoa, chill out!";
    if (has_question_mark)
        return "Sure.";
    return "Whatever.";
}