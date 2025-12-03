import java.util.Random;

class DnDCharacter {

    private final int strength;
    private final int dexterity;
    private final int constitution;
    private final int intelligence;
    private final int wisdom;
    private final int charisma;
    private final int hitpoints;
    private final Random r = new Random();

    public DnDCharacter() {
        this.strength = rolldices();
        this.dexterity = rolldices();
        this.constitution = rolldices();
        this.intelligence = rolldices();
        this.wisdom = rolldices();
        this.charisma = rolldices();
        this.hitpoints = 10 + modifier(this.constitution);
    }

    public int rolldices() {
        int[] values = new int[4];
        for (int i = 0; i < 4; i++) {
            values[i] = r.nextInt(6) + 1;
        }

        int min = values[0];
        int minIndex = 0;
        for (int i = 1; i < 4; i++) {
            if (values[i] < min) {
                min = values[i];
                minIndex = i;
            }
        }

        int sum = 0;
        for (int i = 0; i < 4; i++) {
            if (i != minIndex) {
                sum += values[i];
            }
        }

        return sum;
    }

    int ability() {
        return intelligence;
    }

    int modifier(int input) {
        return (input - 10) / 2;
    }

    int getStrength() {
        return strength;
    }

    int getDexterity() {
        return dexterity;
    }

    int getConstitution() {
        return constitution;
    }

    int getIntelligence() {
        return intelligence;
    }

    int getWisdom() {
        return wisdom;
    }

    int getCharisma() {
        return charisma;
    }

    int getHitpoints() {
        return hitpoints;
    }
}