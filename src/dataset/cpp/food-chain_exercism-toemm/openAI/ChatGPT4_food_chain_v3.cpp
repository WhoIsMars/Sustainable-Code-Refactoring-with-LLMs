#include "food_chain.h"

#include <vector>
#include <string>
#include <sstream>

namespace food_chain {

using namespace std;

const vector<pair<string, pair<string, string>>> lyrics{
    {"fly", {"I know an old lady who swallowed a fly.\n", "I don't know why she swallowed the fly. Perhaps she'll die.\n"}},
    {"spider", {"I know an old lady who swallowed a spider.\n", "It wriggled and jiggled and tickled inside her.\n"}},
    {"bird", {"I know an old lady who swallowed a bird.\n", "How absurd to swallow a bird!\n"}},
    {"cat", {"I know an old lady who swallowed a cat.\n", "Imagine that, to swallow a cat!\n"}},
    {"dog", {"I know an old lady who swallowed a dog.\n", "What a hog, to swallow a dog!\n"}},
    {"goat", {"I know an old lady who swallowed a goat.\n", "Just opened her throat and swallowed a goat!\n"}},
    {"cow", {"I know an old lady who swallowed a cow.\n", "I don't know how she swallowed a cow!\n"}},
    {"horse", {"I know an old lady who swallowed a horse.\n", "She's dead, of course!\n"}}
};

const string alt_bird = " that wriggled and jiggled and tickled inside her.\n";

string verse(int num) {
    stringstream out;
    num--;

    if (num == 7) {
        out << lyrics[num].second.first << lyrics[num].second.second;
        return out.str();
    }

    out << lyrics[num].second.first << lyrics[num].second.second;

    for (int j = num; j > 0; --j) {
        out << "She swallowed the " << lyrics[j].first << " to catch the " << lyrics[j - 1].first;
        if (j == 2) {
            out << alt_bird;
        } else {
            out << ".\n";
        }
    }

    out << lyrics[0].second.second;
    return out.str();
}

string verses(int from, int to) {
    stringstream out;
    for (int i = from; i <= to; ++i) {
        out << verse(i) << "\n";
    }
    return out.str();
}

string sing() {
    return verses(1, 8);
}

}  // namespace food_chain