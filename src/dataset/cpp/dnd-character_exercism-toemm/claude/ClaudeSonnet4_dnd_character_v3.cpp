#include "dnd_character.h"

#include <random>
#include <algorithm>
#include <numeric>

namespace dnd_character {

int modifier(int i) {
    return (i - 10) / 2;
}

int ability() {
    static thread_local std::mt19937 gen(std::random_device{}());
    static thread_local std::uniform_int_distribution<> distrib(1, 6);
    
    int rolls[4];
    for (int i = 0; i < 4; ++i) {
        rolls[i] = distrib(gen);
    }
    
    std::sort(rolls, rolls + 4, std::greater<int>());
    
    return rolls[0] + rolls[1] + rolls[2];
}

Character::Character(): strength(ability()), 
                        dexterity(ability()), 
                        constitution(ability()), 
                        intelligence(ability()),
                        wisdom(ability()),
                        charisma(ability()),
                        hitpoints(10 + modifier(constitution))  {
}

}  // namespace dnd_character