#include "dnd_character.h"
#include <algorithm>
#include <array>
#include <random>

using std::array;

namespace {
    thread_local std::mt19937 rng{std::random_device{}()};
    thread_local std::uniform_int_distribution<int> dice_dist{1, 6};
}

auto dnd_character::ability() -> int {
    array<int, 4> dice_rolls;
    for (int i = 0; i < 4; ++i) {
        dice_rolls[i] = dice_dist(rng);
    }
    
    int min_roll = dice_rolls[0];
    int sum = dice_rolls[0];
    for (int i = 1; i < 4; ++i) {
        if (dice_rolls[i] < min_roll) {
            min_roll = dice_rolls[i];
        }
        sum += dice_rolls[i];
    }
    
    return sum - min_roll;
}

auto dnd_character::modifier(int score) -> int {
    return (score - 10 + (score < 10 ? 1 : 0)) / 2;
}

dnd_character::Character::Character() {
    strength = ability();
    dexterity = ability();
    constitution = ability();
    intelligence = ability();
    wisdom = ability();
    charisma = ability();
    hitpoints = 10 + modifier(constitution);
}