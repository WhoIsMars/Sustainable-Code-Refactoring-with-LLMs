#include "food_chain.h"

#include <utility>
#include <array>
#include <string>

namespace food_chain {

struct AnimalData {
    const char* name;
    const char* intro;
    const char* reaction;
};

constexpr std::array<AnimalData, 8> animals{{
    {"fly", "I know an old lady who swallowed a fly.\n", "I don't know why she swallowed the fly. Perhaps she'll die.\n"},
    {"spider", "I know an old lady who swallowed a spider.\n", "It wriggled and jiggled and tickled inside her.\n"},
    {"bird", "I know an old lady who swallowed a bird.\n", "How absurd to swallow a bird!\n"},
    {"cat", "I know an old lady who swallowed a cat.\n", "Imagine that, to swallow a cat!\n"},
    {"dog", "I know an old lady who swallowed a dog.\n", "What a hog, to swallow a dog!\n"},
    {"goat", "I know an old lady who swallowed a goat.\n", "Just opened her throat and swallowed a goat!\n"},
    {"cow", "I know an old lady who swallowed a cow.\n", "I don't know how she swallowed a cow!\n"},
    {"horse", "I know an old lady who swallowed a horse.\n", "She's dead, of course!\n"}
}};

constexpr const char* alt_bird = " that wriggled and jiggled and tickled inside her.\n";

std::string verse(int num) {
    const int idx = num - 1;
    
    if (idx == 7) {
        return std::string(animals[idx].intro) + animals[idx].reaction;
    }
    
    std::string result;
    result.reserve(256);
    
    result += animals[idx].intro;
    result += animals[idx].reaction;
    
    for (int j = idx; j > 0; --j) {
        result += "She swallowed the ";
        result += animals[j].name;
        result += " to catch the ";
        result += animals[j-1].name;
        result += (j == 2) ? alt_bird : ".\n";
        
        if (j == 1) {
            result += animals[0].reaction;
        }
    }
    
    return result;
}

std::string verses(int from, int to) {
    std::string result;
    result.reserve((to - from + 1) * 256);
    
    for (int i = from; i <= to; ++i) {
        result += verse(i);
        result += '\n';
    }
    
    return result;
}

std::string sing() {
    return verses(1, 8);
}

}  // namespace food_chain