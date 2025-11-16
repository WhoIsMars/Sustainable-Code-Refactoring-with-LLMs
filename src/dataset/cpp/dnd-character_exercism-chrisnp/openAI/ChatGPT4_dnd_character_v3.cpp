#include "dnd_character.h"
#include <algorithm>
#include <array>
#include <numeric>
#include <random>

using std::array;
using std::min_element;
using std::accumulate;

namespace {
    int roll_die() {
        static thread_local std::mt19937 generator(std::random_device{}());
        static std::uniform_int_distribution<int> distribution(1, 6);
        return distribution(generator);
    }
}

auto dnd_character::ability() -> int {
    array<int, 4> dice_rolls;
    std::generate(dice_rolls.begin(), dice_rolls.end(), roll_die);
    return accumulate(dice_rolls.begin(), dice_rolls.end(), 0) - *min_element(dice_rolls.begin(), dice_rolls.end());
}

auto dnd_character::modifier(int score) -> int {
    return (score - 10) / 2;
}

dnd_character::Character::Character()
    : strength{ ability() }
    , dexterity{ ability() }
    , constitution{ ability() }
    , intelligence{ ability() }
    , wisdom{ ability() }
    , charisma{ ability() }
    , hitpoints{ 10 + modifier(constitution) }
{}