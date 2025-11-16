#include "dnd_character.h"

#include <random>
#include <array>
#include <algorithm>
#include <numeric>
#include <chrono>

namespace dnd_character {

int modifier(int i) {
    return (i - 10) / 2;
}

int ability() {
    std::array<int, 4> rolls;
    static thread_local std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> distrib(1, 6);

    for (int& roll : rolls) {
        roll = distrib(gen);
    }

    std::nth_element(rolls.begin(), rolls.begin() + 1, rolls.end(), std::greater<>());
    return std::accumulate(rolls.begin() + 1, rolls.end(), 0);
}

Character::Character()
    : strength(ability()),
      dexterity(ability()),
      constitution(ability()),
      intelligence(ability()),
      wisdom(ability()),
      charisma(ability()),
      hitpoints(10 + modifier(constitution)) {}

}  // namespace dnd_character