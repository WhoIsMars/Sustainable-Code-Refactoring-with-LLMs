#include "yacht.h"

#include <numeric>
#include <algorithm>

namespace yacht {

constexpr const char* ones_to_sixes[] = {"ones", "twos", "threes", "fours", "fives", "sixes"};
constexpr int array_size = sizeof(ones_to_sixes) / sizeof(ones_to_sixes[0]);

int score(std::vector<int> dice, std::string category) {
    int final_score = 0;

    // Ones to sixes
    for (int i = 0; i < array_size; ++i) {
        if (ones_to_sixes[i] == category) {
            int mult = i + 1;
            int count = 0;
            for (int die : dice) {
                if (die == mult) {
                    count++;
                }
            }
            final_score = count * mult;
            return final_score;
        }
    }

    // Other categories
    if (category == "full house") {
        std::array<int, 7> counts = {0};
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
        std::array<int, 7> counts = {0};
        for (int die : dice) {
            counts[die]++;
        }
        if (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 && counts[4] == 1 && counts[5] == 1) {
            final_score = 30;
        }
    } else if (category == "big straight") {
        std::array<int, 7> counts = {0};
        for (int die : dice) {
            counts[die]++;
        }
        if (counts[2] == 1 && counts[3] == 1 && counts[4] == 1 && counts[5] == 1 && counts[6] == 1) {
            final_score = 30;
        }
    } else if (category == "choice") {
        final_score = std::accumulate(dice.begin(), dice.end(), 0);
    } else if (category == "yacht") {
        bool all_same = true;
        for (size_t i = 1; i < dice.size(); ++i) {
            if (dice[i] != dice[0]) {
                all_same = false;
                break;
            }
        }
        if (all_same) {
            final_score = 50;
        }
    }

    return final_score;
}

}  // namespace yacht