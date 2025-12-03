import java.util.Random;

class DnDCharacter {

  private int strength;
  private int dexterity;
  private int constitution;
  private int intelligence;
  private int wisdom;
  private int charisma;
  private int hitpoints;
  private static final Random random = new Random();

  public DnDCharacter() {
    this.strength = calculateAbilityScore();
    this.dexterity = calculateAbilityScore();
    this.constitution = calculateAbilityScore();
    this.intelligence = calculateAbilityScore();
    this.wisdom = calculateAbilityScore();
    this.charisma = calculateAbilityScore();
    this.hitpoints = 10 + modifier(this.constitution);
  }

  private int calculateAbilityScore() {
    int min = 7;
    int sum = 0;
    for (int i = 0; i < 4; i++) {
      int roll = random.nextInt(6) + 1;
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