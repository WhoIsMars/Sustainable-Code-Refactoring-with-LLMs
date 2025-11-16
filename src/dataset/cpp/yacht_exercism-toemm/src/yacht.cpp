#include "yacht.h"

#include <unordered_map>
#include <numeric>

namespace yacht {

constexpr const char* ones_to_sixes[] = {"ones", "twos", "threes", "fours", "fives", "sixes"};

constexpr int array_size = sizeof(ones_to_sixes) / sizeof(ones_to_sixes[0]);

int score(std::vector<int> score, std::string category) {

    int final_score{};
    int mult{};

    for (std::size_t i{}; i < array_size; i++) {
        if (ones_to_sixes[i] == category) {
            mult = i + 1;
            break;
        }
    }

    // category is one of the ones to sixes
    if (mult != 0) {

        for (const auto& num : score) {

            if (mult == num) {
                final_score += 1;
            }
        }

        final_score *= mult;

    // the other categories
    } else {

        std::unordered_map<int, int> score_table;

        for (const auto& num : score) {
            score_table[num]++;
        }

 

        if (category == "full house") {

            int ctr1{};
            int ctr2{};

            for (const auto& [k, v] : score_table) {

                if (v == 2) ctr1++;
                else if (v == 3) ctr2++;

            }

            if (ctr1 == 1 && ctr2 == 1) {
                
                final_score = std::accumulate(score.begin(), score.end(), 0, [] (auto acc, auto el) 
                                {
                                    return acc += el;
                                });

            } else final_score = 0;

        }


        if (category == "four of a kind") {

            for (const auto& [k, v] : score_table) {

                if (v == 4 || v == 5) final_score = 4 * k;
                else final_score = 0;

            }

        }


        int ctr{};
        for (const auto& [k, v] : score_table) {
            if (v == 1) ctr++;
        }


        if (category == "little straight") {

            if (ctr == 5 && score_table[6] == 0) final_score = 30;
            else final_score = 0;

        }

        if (category == "big straight") {

            if (ctr == 5 && score_table[1] == 0) final_score = 30;
            else final_score = 0;
        }

        if (category == "choice") {

            final_score = std::accumulate(score.begin(), score.end(), 0, [] (auto acc, auto el) 
                            {
                                return acc += el;
                            });
        }

        if (category == "yacht") {

            for (const auto& [k, v] : score_table) {

                if (v == 5) final_score = 50;
                else final_score = 0;

            }

        }



    }
    


    return final_score;

}




}  // namespace yacht
