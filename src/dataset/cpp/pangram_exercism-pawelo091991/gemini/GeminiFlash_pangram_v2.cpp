#include "pangram.h"
#include <algorithm>

bool pangram::is_pangram(const string& s) {
    if (s.length() < 26) return false;

    std::bitset<26> data;
    for (char c : s) {
        if (c >= 'a' && c <= 'z') {
            data[c - 'a'] = 1;
        } else if (c >= 'A' && c <= 'Z') {
            data[c - 'A'] = 1;
        }
    }
    return data.all();
}