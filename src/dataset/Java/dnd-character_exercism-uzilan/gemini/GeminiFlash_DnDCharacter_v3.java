import java.util.Random;
import java.util.Arrays;

import static java.lang.Math.floor;

class DnDCharacter {

    private static final Random random = new Random();
    private final int strength = ability();
    private final int dexterity = ability();
    private final int constitution = ability();
    private final int intelligence = ability();
    private final int wisdom = ability();
    private final int charisma = ability();
    private final int hitpoints = 10 + modifier(constitution);

    int ability() {
        int[] rolls = new int[4];
        for (int i = 0; i < 4; i++) {
            rolls[i] = random.nextInt(6) + 1;
        }
        Arrays.sort(rolls);
        return rolls[1] + rolls[2] + rolls[3];
    }

    int modifier(int input) {
        return (int) floor((input - 10) / 2.0);
    }

    public int getStrength() {
        return strength;
    }

    public int getDexterity() {
        return dexterity;
    }

    public int getConstitution() {
        return constitution;
    }

    public int getIntelligence() {
        return intelligence;
    }

    public int getWisdom() {
        return wisdom;
    }

    public int getCharisma() {
        return charisma;
    }

    public int getHitpoints() {
        return hitpoints;
    }
}