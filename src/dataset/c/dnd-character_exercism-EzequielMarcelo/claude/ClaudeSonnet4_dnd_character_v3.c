#include "dnd_character.h"

int ability() 
{
    int rolls[4];
    int min_val = 7;
    int sum = 0;
    
    for (int i = 0; i < 4; i++) {
        rolls[i] = rand() % 6 + 1;
        sum += rolls[i];
        if (rolls[i] < min_val) {
            min_val = rolls[i];
        }
    }
    
    return sum - min_val;
}

int modifier(int score) {
    int diff = score - 10;
    return diff >= 0 ? diff / 2 : (diff - 1) / 2;
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
        .charisma = ability()
    };

    character.hitpoints = 10 + modifier(character.constitution);

    return character;
}