#include "acronym.h"
#include <string>
#include <cctype>
namespace acronym {
    std::string acronym(const std::string& str)
    {
        std::string ans;
        bool newWord = true;
        for (char ch : str) {
            if (std::isalpha(ch)) {
                if (newWord) {
                    ans.push_back(std::toupper(ch));
                    newWord = false;
                }
            } else {
                newWord = true;
            }
        }
        return ans;
    }
}  // namespace acronym