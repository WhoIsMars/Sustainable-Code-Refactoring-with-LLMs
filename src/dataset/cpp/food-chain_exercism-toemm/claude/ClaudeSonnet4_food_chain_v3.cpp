#include "food_chain.h"

#include <utility>
#include <array>
#include <string_view>

namespace food_chain {

struct LyricData {
    std::string_view animal;
    std::string_view intro;
    std::string_view comment;
};

constexpr std::array<LyricData, 8> lyrics{{
    {"fly", "I know an old lady who swallowed a fly.\n", "I don't know why she swallowed the fly. Perhaps she'll die.\n"},
    {"spider", "I know an old lady who swallowed a spider.\n", "It wriggled and jiggled and tickled inside her.\n"},
    {"bird", "I know an old lady who swallowed a bird.\n", "How absurd to swallow a bird!\n"},
    {"cat", "I know an old lady who swallowed a cat.\n", "Imagine that, to swallow a cat!\n"},
    {"dog", "I know an old lady who swallowed a dog.\n", "What a hog, to swallow a dog!\n"},
    {"goat", "I know an old lady who swallowed a goat.\n", "Just opened her throat and swallowed a goat!\n"},
    {"cow", "I know an old lady who swallowed a cow.\n", "I don't know how she swallowed a cow!\n"},
    {"horse", "I know an old lady who swallowed a horse.\n", "She's dead, of course!\n"}
}};

constexpr std::string_view alt_bird = " that wriggled and jiggled and tickled inside her.\n";

std::string verse(int num) {
    const int idx = num - 1;
    
    if (idx == 7) {
        return std::string(lyrics[idx].intro) + std::string(lyrics[idx].comment);
    }
    
    std::string out;
    out.reserve(300);
    
    out += lyrics[idx].intro;
    out += lyrics[idx].comment;
    
    for (int j = idx; j > 0; --j) {
        out += "She swallowed the ";
        out += lyrics[j].animal;
        out += " to catch the ";
        out += lyrics[j-1].animal;
        out += (j == 2) ? alt_bird : ".\n";
        
        if (j == 1) {
            out += lyrics[0].comment;
        }
    }
    
    return out;
}

std::string verses(int from, int to) {
    std::string out;
    out.reserve((to - from + 1) * 300);
    
    for (int i = from; i <= to; ++i) {
        out += verse(i);
        out += '\n';
    }
    
    return out;
}

std::string sing() {
    return verses(1, 8);
}

}  // namespace food_chain