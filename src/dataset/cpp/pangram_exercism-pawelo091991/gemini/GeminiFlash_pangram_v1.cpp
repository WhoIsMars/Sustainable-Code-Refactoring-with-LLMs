#include "pangram.h"
#include <algorithm>

bool pangram::is_pangram(std::string s) {
    if (s.length() < 26) {
        return false;
    }

    std::bitset<26> data;
    s.erase(std::remove_if(s.begin(), s.end(), [](unsigned char c){ return !std::isalpha(c); }), s.end());
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    
    for (const auto& i : s) {
        data[i - 'a'] = 1;
    }
    return data.all();
}