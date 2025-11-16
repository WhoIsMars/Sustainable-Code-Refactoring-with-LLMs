#include "pangram.h"
bool pangram::is_pangram(string s) {
    bitset<26> data;
    for (char i : s) {
        if (i >= 'A' && i <= 'Z') {
            data[i - 'A'] = 1;
        } else if (i >= 'a' && i <= 'z') {
            data[i - 'a'] = 1;
        }
        if (data.all()) return true;
    }
    return false;
}