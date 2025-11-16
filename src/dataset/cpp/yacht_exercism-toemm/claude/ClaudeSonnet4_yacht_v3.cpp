#include "yacht.h"

#include <unordered_map>
#include <numeric>
#include <string_view>

namespace yacht {

constexpr std::string_view ones_to_sixes[] = {"ones", "twos", "threes", "fours", "fives", "sixes"};

int score(std::vector<int> dice, std::string category) {
    const std::string_view cat_view = category;
    
    // Check for ones to sixes categories first
    for (int i = 0; i < 6; ++i) {
        if (ones_to_sixes[i] == cat_view) {
            const int target = i + 1;
            int count = 0;
            for (int die : dice) {
                if (die == target) ++count;
            }
            return count * target;
        }
    }
    
    // Build frequency map once for other categories
    std::unordered_map<int, int> freq;
    freq.reserve(6);
    int sum = 0;
    for (int die : dice) {
        freq[die]++;
        sum += die;
    }
    
    if (cat_view == "full house") {
        bool has_pair = false, has_triple = false;
        for (const auto& [value, count] : freq) {
            if (count == 2) has_pair = true;
            else if (count == 3) has_triple = true;
        }
        return (has_pair && has_triple) ? sum : 0;
    }
    
    if (cat_view == "four of a kind") {
        for (const auto& [value, count] : freq) {
            if (count >= 4) return 4 * value;
        }
        return 0;
    }
    
    if (cat_view == "little straight") {
        return (freq.size() == 5 && freq.find(6) == freq.end()) ? 30 : 0;
    }
    
    if (cat_view == "big straight") {
        return (freq.size() == 5 && freq.find(1) == freq.end()) ? 30 : 0;
    }
    
    if (cat_view == "choice") {
        return sum;
    }
    
    if (cat_view == "yacht") {
        for (const auto& [value, count] : freq) {
            if (count == 5) return 50;
        }
        return 0;
    }
    
    return 0;
}

}  // namespace yacht