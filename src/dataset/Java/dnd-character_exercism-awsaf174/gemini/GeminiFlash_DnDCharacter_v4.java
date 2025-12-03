import java.util.Arrays;
import java.util.Random;

class DnDCharacter {

  private final int strength;
  private final int dexterity;
  private final int constitution;
  private final int intelligence;
  private final int wisdom;
  private final int charisma;
  private final int hitpoints;
  private static final Random random = new Random();

  public DnDCharacter() {
    this.strength = rollDice();
    this.dexterity = rollDice();
    this.constitution = rollDice();
    this.intelligence = rollDice();
    this.wisdom = rollDice();
    this.charisma = rollDice();
    this.hitpoints = 10 + modifier(this.constitution);
  }

  public int rollDice() {
    int[] values = new int[4];
    for (int i = 0; i < 4; i++) {
      values[i] = random.nextInt(6) + 1;
    }
    Arrays.sort(values);
    return values[1] + values[2] + values[3];
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