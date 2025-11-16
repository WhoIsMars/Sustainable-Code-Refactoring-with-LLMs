#include "food_chain.h"

#include <string>
#include <vector>

namespace food_chain {

using namespace std;

const vector<string> animals{
    "fly", "spider", "bird", "cat", "dog", "goat", "cow", "horse"
};

const vector<string> first_lines{
    "I know an old lady who swallowed a fly.\n",
    "I know an old lady who swallowed a spider.\n",
    "I know an old lady who swallowed a bird.\n",
    "I know an old lady who swallowed a cat.\n",
    "I know an old lady who swallowed a dog.\n",
    "I know an old lady who swallowed a goat.\n",
    "I know an old lady who swallowed a cow.\n",
    "I know an old lady who swallowed a horse.\n"
};

const vector<string> second_lines{
    "I don't know why she swallowed the fly. Perhaps she'll die.\n",
    "It wriggled and jiggled and tickled inside her.\n",
    "How absurd to swallow a bird!\n",
    "Imagine that, to swallow a cat!\n",
    "What a hog, to swallow a dog!\n",
    "Just opened her throat and swallowed a goat!\n",
    "I don't know how she swallowed a cow!\n",
    "She's dead, of course!\n"
};

const string alt_bird = " that wriggled and jiggled and tickled inside her.\n";

string verse(int num) {
    string out;
    int index = num - 1;

    out += first_lines[index] + second_lines[index];

    if (index == 7) return out;

    for (int j = index; j > 0; --j) {
        out += "She swallowed the " + animals[j] + " to catch the " + animals[j - 1] + (j == 2 ? alt_bird : ".\n");
    }

    out += second_lines[0];
    return out;
}

string verses(int from, int to) {
    string out;
    for (int i = from; i <= to; ++i) {
        out += verse(i) + (i < to ? "\n" : "");
    }
    return out;
}

string sing() {
    return verses(1, 8);
}

}  // namespace food_chain