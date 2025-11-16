#include "yacht.h"

#include <unordered_map>
#include <numeric>
#include <algorithm>

namespace yacht {

constexpr const char* ones_to_sixes[] = {"ones", "twos", "threes", "fours", "fives", "sixes"};
constexpr int array_size = sizeof(ones_to_sixes) / sizeof(ones_to_sixes[0]);

int score(const std::vector<int>& dice, const std::string& category) {
    if (auto it = std::find(std::begin(ones_to_sixes), std::end(ones_to_sixes), category); it != std::end(ones_to_sixes)) {
        int mult = std::distance(std::begin(ones_to_sixes), it) + 1;
        return std::count(dice.begin(), dice.end(), mult) * mult;
    }

    std::unordered_map<int, int> score_table;
    for (int num : dice) ++score_table[num];

    if (category == "full house") {
        bool has_two = false, has_three = false;
        for (const auto& [_, count] : score_table) {
            if (count == 2) has_two = true;
            if (count == 3) has_three = true;
        }
        return (has_two && has_three) ? std::accumulate(dice.begin(), dice.end(), 0) : 0;
    }

    if (category == "four of a kind") {
        for (const auto& [num, count] : score_table) {
            if (count >= 4) return 4 * num;
        }
        return 0;
    }

    if (category == "little straight") {
        return (score_table.size() == 5 && score_table.count(6) == 0) ? 30 : 0;
    }

    if (category == "big straight") {
        return (score_table.size() == 5 && score_table.count(1) == 0) ? 30 : 0;
    }

    if (category == "choice") {
        return std::accumulate(dice.begin(), dice.end(), 0);
    }

    if (category == "yacht") {
        for (const auto& [_, count] : score_table) {
            if (count == 5) return 50;
        }
        return 0;
    }

    return 0;
}

}  // namespace yacht