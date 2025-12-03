#include "dnd_character.h"

int ability() 
{
    int rolls[4], sum = 0, min_val = 7;
    for (int i = 0; i < 4; i++) {
        rolls[i] = rand() % 6 + 1;
        sum += rolls[i];
        if (rolls[i] < min_val)
            min_val = rolls[i];
    }
    return sum - min_val;
}

int modifier(int score) {
    return (score - 10) / 2;
}

dnd_character_t make_dnd_character() {
    dnd_character_t character;

    srand((unsigned int)time(NULL));

    character.strength = ability();
    character.dexterity = ability();
    character.constitution = ability();
    character.intelligence = ability();
    character.wisdom = ability();
    character.charisma = ability();

    character.hitpoints = 10 + modifier(character.constitution);

    return character;
}