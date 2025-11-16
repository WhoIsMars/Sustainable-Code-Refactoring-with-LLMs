#include "scrabble_score.h"

int scrabble_score::score(const std::string& word) {
    int total = 0;
    const char* ptr = word.data();
    const char* end = ptr + word.size();
    
    while (ptr < end) {
        char c = *ptr++;
        if (c >= 'A' && c <= 'Z') {
            total += LETTER_SCORES[c - 'A'];
        } else if (c >= 'a' && c <= 'z') {
            total += LETTER_SCORES[c - 'a'];
        }
    }
    
    return total;
}