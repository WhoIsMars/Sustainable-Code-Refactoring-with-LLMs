#include "yacht.h"

#include <array>
#include <numeric>

namespace yacht {

int score(std::vector<int> dice, std::string category) {
    
    if (category == "ones") return std::count(dice.begin(), dice.end(), 1);
    if (category == "twos") return 2 * std::count(dice.begin(), dice.end(), 2);
    if (category == "threes") return 3 * std::count(dice.begin(), dice.end(), 3);
    if (category == "fours") return 4 * std::count(dice.begin(), dice.end(), 4);
    if (category == "fives") return 5 * std::count(dice.begin(), dice.end(), 5);
    if (category == "sixes") return 6 * std::count(dice.begin(), dice.end(), 6);
    
    std::array<int, 7> counts{};
    for (int die : dice) {
        counts[die]++;
    }
    
    if (category == "choice") {
        return std::accumulate(dice.begin(), dice.end(), 0);
    }
    
    if (category == "yacht") {
        for (int i = 1; i <= 6; ++i) {
            if (counts[i] == 5) return 50;
        }
        return 0;
    }
    
    if (category == "four of a kind") {
        for (int i = 1; i <= 6; ++i) {
            if (counts[i] >= 4) return 4 * i;
        }
        return 0;
    }
    
    if (category == "full house") {
        bool has_two = false, has_three = false;
        for (int i = 1; i <= 6; ++i) {
            if (counts[i] == 2) has_two = true;
            else if (counts[i] == 3) has_three = true;
        }
        return (has_two && has_three) ? std::accumulate(dice.begin(), dice.end(), 0) : 0;
    }
    
    if (category == "little straight") {
        return (counts[1] && counts[2] && counts[3] && counts[4] && counts[5]) ? 30 : 0;
    }
    
    if (category == "big straight") {
        return (counts[2] && counts[3] && counts[4] && counts[5] && counts[6]) ? 30 : 0;
    }
    
    return 0;
}

}  // namespace yacht