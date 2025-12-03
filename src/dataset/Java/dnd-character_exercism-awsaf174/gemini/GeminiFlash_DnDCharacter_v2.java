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
    this.strength = generateAbilityScore();
    this.dexterity = generateAbilityScore();
    this.constitution = generateAbilityScore();
    this.intelligence = generateAbilityScore();
    this.wisdom = generateAbilityScore();
    this.charisma = generateAbilityScore();
    this.hitpoints = 10 + modifier(this.constitution);
  }

  private int generateAbilityScore() {
    int[] rolls = new int[4];
    for (int i = 0; i < 4; i++) {
      rolls[i] = random.nextInt(6) + 1;
    }
    Arrays.sort(rolls);
    return rolls[1] + rolls[2] + rolls[3];
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

  int ability() {
    return intelligence;
  }
}