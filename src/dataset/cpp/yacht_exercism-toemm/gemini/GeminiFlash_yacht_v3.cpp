#include "yacht.h"

#include <unordered_map>
#include <numeric>
#include <algorithm>

namespace yacht {

constexpr const char* ones_to_sixes[] = {"ones", "twos", "threes", "fours", "fives", "sixes"};
constexpr int array_size = sizeof(ones_to_sixes) / sizeof(ones_to_sixes[0]);

int score(std::vector<int> dice, std::string category) {
    int final_score = 0;

    if (category == "full house") {
        std::unordered_map<int, int> counts;
        for (int die : dice) {
            counts[die]++;
        }

        bool has_two = false;
        bool has_three = false;
        for (const auto& [k, v] : counts) {
            if (v == 2) has_two = true;
            else if (v == 3) has_three = true;
        }

        if (has_two && has_three) {
            final_score = std::accumulate(dice.begin(), dice.end(), 0);
        }
    } else if (category == "four of a kind") {
        std::unordered_map<int, int> counts;
        for (int die : dice) {
            counts[die]++;
        }

        for (const auto& [k, v] : counts) {
            if (v >= 4) {
                final_score = 4 * k;
                break;
            }
        }
    } else if (category == "little straight") {
        std::sort(dice.begin(), dice.end());
        if (dice == std::vector<int>{1, 2, 3, 4, 5}) {
            final_score = 30;
        }
    } else if (category == "big straight") {
        std::sort(dice.begin(), dice.end());
        if (dice == std::vector<int>{2, 3, 4, 5, 6}) {
            final_score = 30;
        }
    } else if (category == "choice") {
        final_score = std::accumulate(dice.begin(), dice.end(), 0);
    } else if (category == "yacht") {
        if (std::all_of(dice.begin(), dice.end(), [&](int die){ return die == dice[0]; })) {
            final_score = 50;
        }
    } else {
        int mult = 0;
        for (std::size_t i = 0; i < array_size; ++i) {
            if (ones_to_sixes[i] == category) {
                mult = i + 1;
                break;
            }
        }

        if (mult != 0) {
            for (int die : dice) {
                if (mult == die) {
                    final_score += mult;
                }
            }
        }
    }

    return final_score;
}

}  // namespace yacht