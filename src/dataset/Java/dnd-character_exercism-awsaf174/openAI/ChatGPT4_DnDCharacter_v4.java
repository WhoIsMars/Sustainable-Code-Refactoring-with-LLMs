import java.util.Random;

class DnDCharacter {

  private final int strength;
  private final int dexterity;
  private final int constitution;
  private final int intelligence;
  private final int wisdom;
  private final int charisma;
  private final int hitpoints;
  private static final Random RANDOM = new Random();

  public DnDCharacter() {
    this.strength = rollDice();
    this.dexterity = rollDice();
    this.constitution = rollDice();
    this.intelligence = rollDice();
    this.wisdom = rollDice();
    this.charisma = rollDice();
    this.hitpoints = 10 + modifier(this.constitution);
  }

  private int rollDice() {
    int[] rolls = new int[4];
    for (int i = 0; i < 4; i++) {
      rolls[i] = RANDOM.nextInt(6) + 1;
    }
    int min = Integer.MAX_VALUE, sum = 0;
    for (int roll : rolls) {
      sum += roll;
      if (roll < min) {
        min = roll;
      }
    }
    return sum - min;
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