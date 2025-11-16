#include "food_chain.h"

#include <string>
#include <vector>

namespace food_chain {

using namespace std;

const array<pair<string, pair<string, string>>, 8> lyrics{
    make_pair("fly", make_pair("I know an old lady who swallowed a fly.\n", "I don't know why she swallowed the fly. Perhaps she'll die.\n")),
    make_pair("spider", make_pair("I know an old lady who swallowed a spider.\n", "It wriggled and jiggled and tickled inside her.\n")),
    make_pair("bird", make_pair("I know an old lady who swallowed a bird.\n", "How absurd to swallow a bird!\n")),
    make_pair("cat", make_pair("I know an old lady who swallowed a cat.\n", "Imagine that, to swallow a cat!\n")),
    make_pair("dog", make_pair("I know an old lady who swallowed a dog.\n", "What a hog, to swallow a dog!\n")),
    make_pair("goat", make_pair("I know an old lady who swallowed a goat.\n", "Just opened her throat and swallowed a goat!\n")),
    make_pair("cow", make_pair("I know an old lady who swallowed a cow.\n", "I don't know how she swallowed a cow!\n")),
    make_pair("horse", make_pair("I know an old lady who swallowed a horse.\n", "She's dead, of course!\n"))
};

const string alt_bird = " that wriggled and jiggled and tickled inside her.\n";

string verse(int num) {
    num--;
    string out;

    if (num == 7) {
        return lyrics[num].second.first + lyrics[num].second.second;
    }

    out.reserve(256); 

    out += lyrics[num].second.first + lyrics[num].second.second;

    for (int j = num; j > 0; --j) {
        out += "She swallowed the " + lyrics[j].first + " to catch the " + lyrics[j - 1].first;
        out += (j == 2) ? alt_bird : ".\n";
        if (j == 1) {
            out += lyrics[0].second.second;
        }
    }

    return out;
}

string verses(int from, int to) {
    string out;
    out.reserve((to - from + 1) * 256);

    for (int i = from; i <= to; ++i) {
        out += verse(i);
        if (i < to) {
            out += "\n";
        }
    }

    return out;
}

string sing() {
    return verses(1, 8);
}

}  // namespace food_chain