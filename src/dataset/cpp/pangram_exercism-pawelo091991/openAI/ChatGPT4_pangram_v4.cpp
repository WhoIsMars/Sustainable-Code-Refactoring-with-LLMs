#include "pangram.h"
bool pangram::is_pangram(const string& s) {
    bitset<26> data;
    for (char c : s) {
        if (isalpha(c)) {
            data.set(tolower(c) - 'a');
            if (data.all()) return true;
        }
    }
    return false;
}