#include "yacht.h"

#include <unordered_map>
#include <numeric>
#include <algorithm>

namespace yacht {

constexpr const char* ones_to_sixes[] = {"ones", "twos", "threes", "fours", "fives", "sixes"};
constexpr int array_size = sizeof(ones_to_sixes) / sizeof(ones_to_sixes[0]);

int score(std::vector<int> dice, std::string category) {
    int final_score = 0;

    auto sum = [](const std::vector<int>& vec) {
        return std::accumulate(vec.begin(), vec.end(), 0);
    };

    auto count_occurrences = [](const std::vector<int>& vec) {
        std::unordered_map<int, int> counts;
        for (int num : vec) {
            counts[num]++;
        }
        return counts;
    };

    auto score_table = count_occurrences(dice);

    auto is_category = [&](const char* cat) {
        return category == cat;
    };

    for (std::size_t i = 0; i < array_size; ++i) {
        if (is_category(ones_to_sixes[i])) {
            int mult = i + 1;
            final_score = std::count(dice.begin(), dice.end(), mult) * mult;
            return final_score;
        }
    }

    if (is_category("full house")) {
        bool has_two = false, has_three = false;
        for (const auto& [num, count] : score_table) {
            if (count == 2) has_two = true;
            if (count == 3) has_three = true;
        }
        final_score = (has_two && has_three) ? sum(dice) : 0;
    } else if (is_category("four of a kind")) {
        for (const auto& [num, count] : score_table) {
            if (count >= 4) {
                final_score = 4 * num;
                break;
            }
        }
    } else if (is_category("little straight")) {
        final_score = (score_table.size() == 5 && score_table[6] == 0) ? 30 : 0;
    } else if (is_category("big straight")) {
        final_score = (score_table.size() == 5 && score_table[1] == 0) ? 30 : 0;
    } else if (is_category("choice")) {
        final_score = sum(dice);
    } else if (is_category("yacht")) {
        for (const auto& [num, count] : score_table) {
            if (count == 5) {
                final_score = 50;
                break;
            }
        }
    }

    return final_score;
}

}  // namespace yacht