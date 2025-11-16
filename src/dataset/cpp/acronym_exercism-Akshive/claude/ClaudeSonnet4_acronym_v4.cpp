#include "acronym.h"
#include <string>
#include <cctype>

namespace acronym {
    std::string acronym(std::string str)
    {
        std::string ans;
        ans.reserve(str.length() / 4);
        
        bool start_of_word = true;
        
        for (char c : str) {
            if (std::isalpha(c)) {
                if (start_of_word) {
                    ans.push_back(std::toupper(c));
                    start_of_word = false;
                }
            } else {
                start_of_word = true;
            }
        }
        
        return ans;
    }
}