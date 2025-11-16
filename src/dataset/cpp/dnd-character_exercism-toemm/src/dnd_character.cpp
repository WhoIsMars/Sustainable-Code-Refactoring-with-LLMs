#include "dnd_character.h"

#include <random>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>
#include <numeric>

namespace dnd_character {


int modifier(int i) {



    double out = (i - 10) / 2.0;

    return floor(out);
}

int ability() {

    std::vector<int> rolls; 
    std::mt19937 gen(time(0));  
    std::uniform_int_distribution<> distrib(1, 6); 

    for (int i{}; i < 4; i++) {
        rolls.push_back(static_cast<int>(distrib(gen)));
    }


    int sum{};

    std::sort(rolls.begin(), rolls.end(), [] (int i, int j) { return i > j; });

    sum = std::accumulate(rolls.begin()+1, rolls.end(), 0); 

    return sum;


}

Character::Character(): strength(ability()), 
                        dexterity(ability()), 
                        constitution(ability()), 
                        intelligence(ability()),
                        wisdom(ability()),
                        charisma(ability()),
                        hitpoints(10 + modifier(this->constitution))  {

}



}  // namespace dnd_character
