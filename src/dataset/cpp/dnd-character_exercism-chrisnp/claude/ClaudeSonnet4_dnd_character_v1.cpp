#include "dnd_character.h"
#include <algorithm>
#include <numeric>

auto dnd_character::ability() -> int {
    int dice_rolls[4];
    int min_roll = 6;
    int sum = 0;
    
    for (int i = 0; i < 4; ++i) {
        dice_rolls[i] = 1 + std::rand() % 6;
        sum += dice_rolls[i];
        if (dice_rolls[i] < min_roll) {
            min_roll = dice_rolls[i];
        }
    }
    
    return sum - min_roll;
}

auto dnd_character::modifier(int score) -> int {
    return (score - 10 - (score < 10)) / 2;
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