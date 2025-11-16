#include "yacht.h"

#include <unordered_map>
#include <numeric>

namespace yacht {

int score(std::vector<int> score, std::string category) {
    
    // Handle ones to sixes categories
    if (category.size() >= 4) {
        char first_char = category[0];
        if (first_char >= 'o' && first_char <= 't') {
            int mult = 0;
            switch (first_char) {
                case 'o': mult = 1; break; // ones
                case 't': mult = (category[1] == 'w') ? 2 : 3; break; // twos or threes
                case 'f': mult = (category[1] == 'o') ? 4 : 5; break; // fours or fives
                case 's': mult = 6; break; // sixes
            }
            
            if (mult > 0) {
                int count = 0;
                for (int num : score) {
                    if (num == mult) count++;
                }
                return count * mult;
            }
        }
    }

    // Build frequency map for other categories
    std::unordered_map<int, int> freq;
    for (int num : score) {
        freq[num]++;
    }

    char first_char = category[0];
    
    switch (first_char) {
        case 'f': { // full house
            bool has_pair = false, has_triple = false;
            for (const auto& [k, v] : freq) {
                if (v == 2) has_pair = true;
                else if (v == 3) has_triple = true;
            }
            return (has_pair && has_triple) ? std::accumulate(score.begin(), score.end(), 0) : 0;
        }
        
        case 'y': // yacht
            for (const auto& [k, v] : freq) {
                if (v == 5) return 50;
            }
            return 0;
            
        case 'c': // choice
            return std::accumulate(score.begin(), score.end(), 0);
            
        case 'l': // little straight
            return (freq.size() == 5 && freq.count(6) == 0) ? 30 : 0;
            
        case 'b': // big straight
            return (freq.size() == 5 && freq.count(1) == 0) ? 30 : 0;
            
        default: // four of a kind
            for (const auto& [k, v] : freq) {
                if (v >= 4) return 4 * k;
            }
            return 0;
    }
}

}  // namespace yacht