import java.util.concurrent.ThreadLocalRandom;
import java.util.Arrays;

class DnDCharacter {

    private final int strength;
    private final int dexterity;
    private final int constitution;
    private final int intelligence;
    private final int wisdom;
    private final int charisma;
    private final int hitpoints;

    public DnDCharacter() {
        this.strength = ability();
        this.dexterity = ability();
        this.constitution = ability();
        this.intelligence = ability();
        this.wisdom = ability();
        this.charisma = ability();
        this.hitpoints = 10 + modifier(constitution);
    }

    int ability() {
        int[] rolls = new int[4];
        for (int i = 0; i < 4; i++) {
            rolls[i] = throwDie(6);
        }
        Arrays.sort(rolls);
        return rolls[1] + rolls[2] + rolls[3];
    }

    int modifier(int input) {
        return (input - 10) / 2;
    }

    int throwDie(int sides) {
        return ThreadLocalRandom.current().nextInt(1, sides + 1);
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

    int getHitpoints() {
        return hitpoints;
    }
}