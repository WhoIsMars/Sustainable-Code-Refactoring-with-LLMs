#include "food_chain.h"

constexpr VERSE_INFO song_info[] = {
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

std::string food_chain::verse(int num) {
    std::string res = "I know an old lady who swallowed a " + song_info[num].animal + ".\n";

    if (num > FLY) {
        res += song_info[num].reaction + "\n";
    }

    if (num == HORSE) return res;

    for (int i = num; i > FLY; --i) {
        res += "She swallowed the " + song_info[i].animal + " to catch the " + song_info[i - 1].animal;
        if (i - 1 == SPIDER) {
            res += " that wriggled and jiggled and tickled inside her.\n";
        } else {
            res += ".\n";
        }
    }

    res += song_info[FLY].reaction + "\n";
    return res;
}

std::string food_chain::verses(int start, int end) {
    std::string res;
    res.reserve(1024); // Pre-allocate memory to reduce reallocations
    for (int i = start; i <= end; ++i) {
        res += verse(i) + "\n";
    }
    return res;
}

std::string food_chain::sing() {
    return verses(1, 8);
}