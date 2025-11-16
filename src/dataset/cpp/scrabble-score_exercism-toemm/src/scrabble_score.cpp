#include "scrabble_score.h"

#include <unordered_map>
#include <vector>


namespace scrabble_score {


const std::unordered_map<int, std::vector<char>> scores = {
    {1, {'a','e','i','o','u','l','n','r','s','t'}},
    {2, {'d','g'}},
    {3, {'b','c','m','p'}},
    {4, {'f','h','v','w','y'}},
    {5, {'k'}},
    {8, {'j','x'}},
    {10, {'q','z'}},
};

int score(const std::string& str) {

    int score{};

    for (const auto& ch : str) {

        for (const auto& [k , v] : scores) {

            for (const auto& v_ch : v) {
                
                if (std::tolower(ch) == v_ch) {
                    score += k;
                    break;
                }
            }
        }
    }

    return score;


}

}  // namespace scrabble_score
