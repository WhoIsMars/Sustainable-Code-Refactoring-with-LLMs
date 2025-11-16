#include "dnd_character.h"
#include <algorithm>
#include <array>
#include <numeric>

using std::array;
using std::min_element;
using std::accumulate;

auto dnd_character::ability() -> int {
    auto roll = [=]() { return 1 + std::rand() % 6; };
    array<int, 4> dice_rolls {}; 
    for (int i = 0; i <= 3; ++i) dice_rolls[i] = roll();
    auto discard = *min_element(dice_rolls.begin(), dice_rolls.end());
    return accumulate(dice_rolls.begin(), dice_rolls.end(), -discard);
}

auto dnd_character::modifier(int score) -> int {
    int ability = score - 10;
    return (ability - (ability < 0)) / 2;
}

dnd_character::Character::Character() 
                          : strength{ ability() }
                          , dexterity{ ability() }
                          , constitution{ ability() }
                          , intelligence{ ability() }
                          , wisdom{ ability() }
                          , charisma{ ability() }
                          , hitpoints{ 10 + modifier(constitution) }
                          {};

