#include "dnd_character.h"
#include <algorithm>

int ability() {
    int rolls[4];
    for (int i = 0; i < 4; ++i) {
        rolls[i] = rand() % 6 + 1;
    }

    int min_roll = rolls[0];
    for (int i = 1; i < 4; ++i) {
        if (rolls[i] < min_roll) {
            min_roll = rolls[i];
        }
    }

    int sum = 0;
    for (int i = 0; i < 4; ++i) {
        if (rolls[i] != min_roll || min_roll != *std::min_element(rolls, rolls + 4))
            sum += rolls[i];
        else if (rolls[i] == min_roll)
        {
            rolls[i] = 7;
        }
    }
    return sum;
}

int modifier(int score) {
    return (score - 10) / 2;
}

dnd_character_t make_dnd_character() {
    dnd_character_t character;

    character.strength = ability();
    character.dexterity = ability();
    character.constitution = ability();
    character.intelligence = ability();
    character.wisdom = ability();
    character.charisma = ability();

    character.hitpoints = 10 + modifier(character.constitution);

    return character;
}