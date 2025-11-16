#include "dnd_character.h"
#include <algorithm>
#include <array>
#include <numeric>
#include <random>

using std::array;
using std::min_element;
using std::accumulate;

namespace {
    thread_local std::mt19937 rng{std::random_device{}()};
    thread_local std::uniform_int_distribution<int> dice_dist{1, 6};
}

auto dnd_character::ability() -> int {
    array<int, 4> dice_rolls;
    for (int& roll : dice_rolls) {
        roll = dice_dist(rng);
    }
    
    int min_roll = *min_element(dice_rolls.begin(), dice_rolls.end());
    return accumulate(dice_rolls.begin(), dice_rolls.end(), -min_roll);
}

auto dnd_character::modifier(int score) -> int {
    return (score - 10) >> 1;
}

dnd_character::Character::Character() 
                          : constitution{ ability() }
                          , strength{ ability() }
                          , dexterity{ ability() }
                          , intelligence{ ability() }
                          , wisdom{ ability() }
                          , charisma{ ability() }
                          , hitpoints{ 10 + modifier(constitution) }
                          {};