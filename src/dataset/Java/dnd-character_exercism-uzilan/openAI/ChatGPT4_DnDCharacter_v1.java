import java.util.Random;

import static java.lang.Math.floor;

class DnDCharacter {

    private static final Random RANDOM = new Random();
    private final int strength = ability();
    private final int dexterity = ability();
    private final int constitution = ability();
    private final int intelligence = ability();
    private final int wisdom = ability();
    private final int charisma = ability();
    private final int hitpoints = 10 + modifier(constitution);

    int ability() {
        int[] rolls = new int[4];
        int min = Integer.MAX_VALUE, sum = 0;
        for (int i = 0; i < 4; i++) {
            rolls[i] = RANDOM.nextInt(6) + 1;
            sum += rolls[i];
            if (rolls[i] < min) {
                min = rolls[i];
            }
        }
        return sum - min;
    }

    int modifier(int input) {
        return (input - 10) / 2;
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