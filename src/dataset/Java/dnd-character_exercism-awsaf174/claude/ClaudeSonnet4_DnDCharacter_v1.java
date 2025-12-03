import java.util.Random;

class DnDCharacter {

  private int strength;
  private int dexterity;
  private int constitution;
  private int intelligence;
  private int wisdom;
  private int charisma;
  private int hitpoints;
  private Random r = new Random();

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
    int[] rolls = new int[4];
    for(int i = 0; i < 4; i++) {
      rolls[i] = r.nextInt(6) + 1;
    }

    int min = rolls[0];
    int sum = rolls[0];
    for(int i = 1; i < 4; i++) {
      sum += rolls[i];
      if(rolls[i] < min) {
        min = rolls[i];
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