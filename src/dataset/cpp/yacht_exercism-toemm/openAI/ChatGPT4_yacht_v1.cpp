#include "yacht.h"

#include <unordered_map>
#include <numeric>
#include <algorithm>

namespace yacht {

constexpr const char* ones_to_sixes[] = {"ones", "twos", "threes", "fours", "fives", "sixes"};
constexpr int array_size = sizeof(ones_to_sixes) / sizeof(ones_to_sixes[0]);

int score(std::vector<int> score, std::string category) {
    int final_score = 0;

    auto sum = [](const std::vector<int>& vec) {
        return std::accumulate(vec.begin(), vec.end(), 0);
    };

    auto count_occurrences = [](const std::vector<int>& vec) {
        std::unordered_map<int, int> freq;
        for (int num : vec) ++freq[num];
        return freq;
    };

    auto score_table = count_occurrences(score);

    // Handle "ones" to "sixes"
    auto it = std::find(ones_to_sixes, ones_to_sixes + array_size, category);
    if (it != ones_to_sixes + array_size) {
        int mult = std::distance(ones_to_sixes, it) + 1;
        final_score = std::count(score.begin(), score.end(), mult) * mult;
        return final_score;
    }

    // Handle other categories
    if (category == "full house") {
        bool has_two = false, has_three = false;
        for (const auto& [_, v] : score_table) {
            if (v == 2) has_two = true;
            if (v == 3) has_three = true;
        }
        final_score = (has_two && has_three) ? sum(score) : 0;
    } else if (category == "four of a kind") {
        for (const auto& [k, v] : score_table) {
            if (v >= 4) {
                final_score = 4 * k;
                break;
            }
        }
    } else if (category == "little straight") {
        final_score = (score_table.size() == 5 && score_table[6] == 0) ? 30 : 0;
    } else if (category == "big straight") {
        final_score = (score_table.size() == 5 && score_table[1] == 0) ? 30 : 0;
    } else if (category == "choice") {
        final_score = sum(score);
    } else if (category == "yacht") {
        for (const auto& [_, v] : score_table) {
            if (v == 5) {
                final_score = 50;
                break;
            }
        }
    }

    return final_score;
}

}  // namespace yacht