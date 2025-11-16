#include "yacht.h"

#include <unordered_map>
#include <numeric>
#include <string_view>

namespace yacht {

int score(std::vector<int> dice, std::string category) {
    
    // Use string_view for faster string comparisons
    std::string_view cat_view(category);
    
    // Handle ones to sixes categories
    if (cat_view.size() >= 4) {
        int mult = 0;
        switch (cat_view[0]) {
            case 'o': mult = 1; break; // ones
            case 't': mult = cat_view[1] == 'w' ? 2 : 3; break; // twos or threes
            case 'f': mult = cat_view[1] == 'o' ? 4 : 5; break; // fours or fives
            case 's': mult = 6; break; // sixes
        }
        
        if (mult != 0) {
            int count = 0;
            for (int die : dice) {
                if (die == mult) count++;
            }
            return count * mult;
        }
    }
    
    // Build frequency map once for other categories
    int freq[7] = {0}; // indices 1-6 for dice values
    for (int die : dice) {
        freq[die]++;
    }
    
    switch (cat_view[0]) {
        case 'f': { // full house
            bool has_two = false, has_three = false;
            for (int i = 1; i <= 6; i++) {
                if (freq[i] == 2) has_two = true;
                else if (freq[i] == 3) has_three = true;
            }
            return (has_two && has_three) ? std::accumulate(dice.begin(), dice.end(), 0) : 0;
        }
        
        case 'l': { // little straight (1-5)
            return (freq[1] == 1 && freq[2] == 1 && freq[3] == 1 && 
                   freq[4] == 1 && freq[5] == 1) ? 30 : 0;
        }
        
        case 'b': { // big straight (2-6)
            return (freq[2] == 1 && freq[3] == 1 && freq[4] == 1 && 
                   freq[5] == 1 && freq[6] == 1) ? 30 : 0;
        }
        
        case 'c': // choice
            return std::accumulate(dice.begin(), dice.end(), 0);
            
        case 'y': { // yacht
            for (int i = 1; i <= 6; i++) {
                if (freq[i] == 5) return 50;
            }
            return 0;
        }
        
        default: { // four of a kind
            for (int i = 1; i <= 6; i++) {
                if (freq[i] >= 4) return 4 * i;
            }
            return 0;
        }
    }
}

}  // namespace yacht