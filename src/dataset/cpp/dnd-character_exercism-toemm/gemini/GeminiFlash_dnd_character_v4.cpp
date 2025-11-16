#include "dnd_character.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

namespace dnd_character {

int modifier(int i) { return (i - 10) / 2; }

int ability() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, 6);

  std::vector<int> rolls(4);
  for (int& roll : rolls) {
    roll = distrib(gen);
  }

  std::sort(rolls.begin(), rolls.end());

  return std::accumulate(rolls.begin() + 1, rolls.end(), 0);
}

Character::Character()
    : strength(ability()), dexterity(ability()), constitution(ability()),
      intelligence(ability()), wisdom(ability()), charisma(ability()),
      hitpoints(10 + modifier(constitution)) {}

} // namespace dnd_character