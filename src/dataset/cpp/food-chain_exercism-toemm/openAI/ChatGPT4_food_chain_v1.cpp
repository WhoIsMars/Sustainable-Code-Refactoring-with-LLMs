#include "food_chain.h"

#include <vector>
#include <string>

namespace food_chain {

const std::vector<std::string> animals{
    "fly", "spider", "bird", "cat", "dog", "goat", "cow", "horse"
};

const std::vector<std::string> first_lines{
    "I know an old lady who swallowed a fly.\n",
    "I know an old lady who swallowed a spider.\n",
    "I know an old lady who swallowed a bird.\n",
    "I know an old lady who swallowed a cat.\n",
    "I know an old lady who swallowed a dog.\n",
    "I know an old lady who swallowed a goat.\n",
    "I know an old lady who swallowed a cow.\n",
    "I know an old lady who swallowed a horse.\n"
};

const std::vector<std::string> second_lines{
    "I don't know why she swallowed the fly. Perhaps she'll die.\n",
    "It wriggled and jiggled and tickled inside her.\n",
    "How absurd to swallow a bird!\n",
    "Imagine that, to swallow a cat!\n",
    "What a hog, to swallow a dog!\n",
    "Just opened her throat and swallowed a goat!\n",
    "I don't know how she swallowed a cow!\n",
    "She's dead, of course!\n"
};

const std::string alt_bird = " that wriggled and jiggled and tickled inside her.\n";

std::string verse(int num) {
    num--;
    std::string out;

    out += first_lines[num] + second_lines[num];

    if (num == 7) {
        return out; // Special case for the horse
    }

    for (int j = num; j > 0; --j) {
        out += "She swallowed the " + animals[j] + " to catch the " + animals[j - 1] + (j == 2 ? alt_bird : ".\n");
    }

    out += second_lines[0];
    return out;
}

std::string verses(int from, int to) {
    std::string out;
    for (int i = from; i <= to; ++i) {
        if (!out.empty()) out += "\n";
        out += verse(i);
    }
    return out;
}

std::string sing() {
    return verses(1, 8);
}

}  // namespace food_chain