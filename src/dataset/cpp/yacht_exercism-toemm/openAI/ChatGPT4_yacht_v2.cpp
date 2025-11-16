#include "yacht.h"

#include <unordered_map>
#include <numeric>
#include <algorithm>

namespace yacht {

constexpr const char* ones_to_sixes[] = {"ones", "twos", "threes", "fours", "fives", "sixes"};
constexpr int array_size = sizeof(ones_to_sixes) / sizeof(ones_to_sixes[0]);

int score(const std::vector<int>& dice, const std::string& category) {
    int final_score = 0;

    auto sum_dice = [](const std::vector<int>& dice) {
        return std::accumulate(dice.begin(), dice.end(), 0);
    };

    auto count_occurrences = [](const std::vector<int>& dice) {
        std::unordered_map<int, int> counts;
        for (int num : dice) {
            counts[num]++;
        }
        return counts;
    };

    auto score_table = count_occurrences(dice);

    // Handle "ones" to "sixes"
    auto it = std::find(std::begin(ones_to_sixes), std::end(ones_to_sixes), category);
    if (it != std::end(ones_to_sixes)) {
        int mult = std::distance(std::begin(ones_to_sixes), it) + 1;
        final_score = std::count(dice.begin(), dice.end(), mult) * mult;
        return final_score;
    }

    // Handle other categories
    if (category == "full house") {
        bool has_two = false, has_three = false;
        for (const auto& [_, count] : score_table) {
            if (count == 2) has_two = true;
            if (count == 3) has_three = true;
        }
        final_score = (has_two && has_three) ? sum_dice(dice) : 0;
    } else if (category == "four of a kind") {
        for (const auto& [num, count] : score_table) {
            if (count >= 4) {
                final_score = 4 * num;
                break;
            }
        }
    } else if (category == "little straight") {
        final_score = (score_table.size() == 5 && score_table.count(6) == 0) ? 30 : 0;
    } else if (category == "big straight") {
        final_score = (score_table.size() == 5 && score_table.count(1) == 0) ? 30 : 0;
    } else if (category == "choice") {
        final_score = sum_dice(dice);
    } else if (category == "yacht") {
        final_score = (score_table.size() == 1 && score_table.begin()->second == 5) ? 50 : 0;
    }

    return final_score;
}

}  // namespace yacht