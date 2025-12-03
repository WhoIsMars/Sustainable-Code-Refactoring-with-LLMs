#include "dnd_character.h"
#include <algorithm>
#include <numeric>

int ability() {
    int rolls[4];
    for (int i = 0; i < 4; ++i) {
        rolls[i] = rand() % 6 + 1;
    }

    int min_val = rolls[0];
    int sum = rolls[0];
    for (int i = 1; i < 4; ++i) {
        sum += rolls[i];
        if (rolls[i] < min_val) {
            min_val = rolls[i];
        }
    }

    return sum - min_val;
}

int modifier(int score) {
    return (score - 10) / 2;
}

dnd_character_t make_dnd_character() {
    dnd_character_t character;

    static bool seeded = false;
    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    character.strength = ability();
    character.dexterity = ability();
    character.constitution = ability();
    character.intelligence = ability();
    character.wisdom = ability();
    character.charisma = ability();

    character.hitpoints = 10 + modifier(character.constitution);

    return character;
}