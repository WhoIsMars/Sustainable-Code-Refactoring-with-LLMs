#include "dnd_character.h"

int ability() 
{
    int rolls[4];
    int min_val = 7; // Initialize to max possible value + 1
    int sum = 0;
    
    for (int i = 0; i < 4; i++) 
    {
        rolls[i] = rand() % 6 + 1;
        sum += rolls[i];
        if (rolls[i] < min_val)
            min_val = rolls[i];
    }
    
    return sum - min_val;
}

int modifier(int score) {
    int diff = score - 10;
    return diff >= 0 ? diff / 2 : (diff - 1) / 2;
}

dnd_character_t make_dnd_character() {
    dnd_character_t character;

    // Seed the random number generator
    srand(time(NULL));

    // Generate abilities
    character.strength = ability();
    character.dexterity = ability();
    character.constitution = ability();
    character.intelligence = ability();
    character.wisdom = ability();
    character.charisma = ability();

    // Calculate hitpoints
    character.hitpoints = 10 + modifier(character.constitution);

    return character;
}