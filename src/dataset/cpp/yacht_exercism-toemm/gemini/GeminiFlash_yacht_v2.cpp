#include "yacht.h"

#include <numeric>
#include <algorithm>

namespace yacht {

constexpr const char* ones_to_sixes[] = {"ones", "twos", "threes", "fours", "fives", "sixes"};
constexpr int array_size = sizeof(ones_to_sixes) / sizeof(ones_to_sixes[0]);

int score(std::vector<int> dice, std::string category) {
    int final_score = 0;

    // Ones to sixes categories
    for (int i = 0; i < array_size; ++i) {
        if (ones_to_sixes[i] == category) {
            int target_number = i + 1;
            for (int die : dice) {
                if (die == target_number) {
                    final_score += target_number;
                }
            }
            return final_score;
        }
    }

    // Other categories
    if (category == "full house") {
        std::sort(dice.begin(), dice.end());
        if ((dice[0] == dice[1] && dice[2] == dice[3] && dice[3] == dice[4] && dice[1] != dice[2]) ||
            (dice[0] == dice[1] && dice[1] == dice[2] && dice[3] == dice[4] && dice[2] != dice[3])) {
            final_score = std::accumulate(dice.begin(), dice.end(), 0);
        }
    } else if (category == "four of a kind") {
        std::sort(dice.begin(), dice.end());
        if (dice[0] == dice[3]) {
            final_score = 4 * dice[0];
        } else if (dice[1] == dice[4]) {
            final_score = 4 * dice[1];
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
    }

    return final_score;
}

}  // namespace yacht