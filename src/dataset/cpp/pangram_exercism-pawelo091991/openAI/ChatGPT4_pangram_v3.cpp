#include "pangram.h"
bool pangram::is_pangram(string s) {
    bitset<26> data;
    for (char i : s) {
        if (unsigned char c = tolower(i); c >= 'a' && c <= 'z') {
            data[c - 'a'] = 1;
            if (data.all()) return true;
        }
    }
    return false;
}