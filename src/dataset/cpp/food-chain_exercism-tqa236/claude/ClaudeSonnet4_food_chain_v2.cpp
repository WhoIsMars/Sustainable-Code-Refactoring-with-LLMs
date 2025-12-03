#include "food_chain.h"

static const VERSE_INFO song_info[] = {
    {},
    {"fly", "I don't know why she swallowed the fly. Perhaps she'll die."},
    {"spider", "It wriggled and jiggled and tickled inside her."},
    {"bird", "How absurd to swallow a bird!"},
    {"cat", "Imagine that, to swallow a cat!"},
    {"dog", "What a hog, to swallow a dog!"},
    {"goat", "Just opened her throat and swallowed a goat!"},
    {"cow", "I don't know how she swallowed a cow!"},
    {"horse", "She's dead, of course!"},
};

static const char* const COMMON_PREFIX = "I know an old lady who swallowed a ";
static const char* const CATCH_PREFIX = "She swallowed the ";
static const char* const CATCH_MIDDLE = " to catch the ";
static const char* const SPIDER_SUFFIX = " that wriggled and jiggled and tickled inside her.\n";

std::string food_chain::verse(int num) {
    std::string res;
    res.reserve(256);
    
    res += COMMON_PREFIX;
    res += song_info[num].animal;
    res += ".\n";

    if (num > FLY) {
        res += song_info[num].reaction;
        res += '\n';
    }

    if (num == HORSE) return res;

    while (num > FLY) {
        res += CATCH_PREFIX;
        res += song_info[num].animal;
        res += CATCH_MIDDLE;
        res += song_info[num - 1].animal;
        
        if (--num == SPIDER) {
            res += SPIDER_SUFFIX;
        } else {
            res += ".\n";
        }
    }

    res += song_info[FLY].reaction;
    res += '\n';
    
    return res;
}

std::string food_chain::verses(int start, int end) {
    std::string res;
    res.reserve((end - start + 1) * 256);
    
    for (int i = start; i <= end; i++) {
        res += verse(i);
        res += '\n';
    }
    return res;
}

std::string food_chain::sing() { 
    return verses(1, 8); 
}