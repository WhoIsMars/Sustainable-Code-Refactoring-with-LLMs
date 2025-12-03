#include "dnd_character.h"
#include <algorithm>

int ability() {
    int rolls[4];
    for (int i = 0; i < 4; ++i) {
        rolls[i] = rand() % 6 + 1;
    }

    // Find the minimum value directly using std::min_element
    int* min_element_ptr = std::min_element(rolls, rolls + 4);
    int min_val = *min_element_ptr;

    int sum = 0;
    for (int i = 0; i < 4; ++i) {
        sum += rolls[i];
    }

    return sum - min_val;
}

int modifier(int score) {
    return (score - 10) / 2;
}

dnd_character_t make_dnd_character() {
    dnd_character_t character;

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