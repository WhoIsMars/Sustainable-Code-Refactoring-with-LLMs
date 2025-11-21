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
        std::array<int, 7> counts = {0}; // Indices 1-6 represent dice values
        for (int die : dice) {
            counts[die]++;
        }

        bool has_two = false;
        bool has_three = false;
        for (int i = 1; i <= 6; ++i) {
            if (counts[i] == 2) has_two = true;
            if (counts[i] == 3) has_three = true;
        }

        if (has_two && has_three) {
            final_score = std::accumulate(dice.begin(), dice.end(), 0);
        }
    } else if (category == "four of a kind") {
        std::array<int, 7> counts = {0};
        for (int die : dice) {
            counts[die]++;
        }

        for (int i = 1; i <= 6; ++i) {
            if (counts[i] >= 4) {
                final_score = 4 * i;
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
        if (std::adjacent_find(dice.begin(), dice.end(), std::not_equal_to<int>()) == dice.end()) {
            final_score = 50;
        }
    }

    return final_score;
}

}  // namespace yacht