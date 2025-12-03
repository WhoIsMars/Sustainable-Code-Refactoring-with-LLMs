#include "scrabble_score.h"
#include <ctype.h>
#include <string.h>

unsigned int score(const char *word) {
    unsigned int total_score = 0;
    if (word == NULL) {
        return 0;
    }

    for (const char *p = word; *p != '\0'; ++p) {
        char lower_char = tolower((unsigned char)*p); 

        int char_score = 0;
        switch (lower_char) {
            case 'a': case 'e': case 'i': case 'o': case 'u':
            case 'l': case 'n': case 'r': case 's': case 't':
                char_score = 1;
                break;
            case 'd': case 'g':
                char_score = 2;
                break;
            case 'b': case 'c': case 'm': case 'p':
                char_score = 3;
                break;
            case 'f': case 'h': case 'v': case 'w': case 'y':
                char_score = 4;
                break;
            case 'k':
                char_score = 5;
                break;
            case 'j': case 'x':
                char_score = 8;
                break;
            case 'q': case 'z':
                char_score = 10;
                break;
            default:
                char_score = 0;
                break;
        }
        total_score += char_score;
    }

    return total_score;
}