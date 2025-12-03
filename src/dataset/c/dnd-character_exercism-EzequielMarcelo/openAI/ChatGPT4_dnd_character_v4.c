#include "dnd_character.h"
#include <stdlib.h>
#include <time.h>

int ability() 
{
    int rolls[4] = {rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1, rand() % 6 + 1};
    int min_value = rolls[0], sum = rolls[0] + rolls[1] + rolls[2] + rolls[3];

    for (int i = 1; i < 4; i++) 
        if (rolls[i] < min_value)
            min_value = rolls[i];

    return sum - min_value;
}

int modifier(int score) {
    return (score - 10) / 2;
}

dnd_character_t make_dnd_character() {
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    dnd_character_t character = {
        .strength = ability(),
        .dexterity = ability(),
        .constitution = ability(),
        .intelligence = ability(),
        .wisdom = ability(),
        .charisma = ability(),
        .hitpoints = 10 + modifier(ability())
    };

    return character;
}