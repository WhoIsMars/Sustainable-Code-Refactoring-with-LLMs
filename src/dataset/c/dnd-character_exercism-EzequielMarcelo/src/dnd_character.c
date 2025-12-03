#include "dnd_character.h"

int ability() 
{
    int rolls[4];
    for (int i = 0; i < 4; i++) 
        rolls[i] = rand() % 6 + 1;

    int min_index = 0;
    for (int i = 1; i < 4; i++) 
    {
        if (rolls[i] < rolls[min_index])
            min_index = i;        
    }

    int sum = 0;
    for (int i = 0; i < 4; i++) 
    {
        if (i != min_index) 
            sum += rolls[i];
        
    }    
    return sum;
}

int modifier(int score) {
    return (score - 10) / 2 - ((score - 10) % 2 && (score - 10) < 0 ? 1 : 0);
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