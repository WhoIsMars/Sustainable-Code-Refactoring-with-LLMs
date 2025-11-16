#include "acronym.h"

#include <algorithm>

namespace acronym {

std::string acronym(const std::string& sentence) {

    std::string acronym;

    std::string ssentence = sentence;


    // replace hyphens with whitespaces
    std::replace_if(ssentence.begin(), ssentence.end(),
                    [] (unsigned char ch) { return ch == '-'; },
                    ' ');

    // strip everything else
    ssentence.erase(std::remove_if(ssentence.begin(), ssentence.end(),
                    [] (unsigned char ch) { return !isalpha(ch) && ch != ' '; }), ssentence.end());


    bool new_word = true;


    for (char ch : ssentence) {



        if (new_word && ch != ' ') {
            acronym.push_back(toupper(ch));
            new_word = false;
        }

        if (ch == ' ') new_word = true;
    }


    return acronym;
}

}  // namespace acronym
