import java.util.Random;
import java.util.stream.IntStream;

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
    this.strength = rollDices();
    this.dexterity = rollDices();
    this.constitution = rollDices();
    this.intelligence = rollDices();
    this.wisdom = rollDices();
    this.charisma = rollDices();
    this.hitpoints = 10 + modifier(this.constitution);
  }

  private int rollDices() {
    return IntStream.generate(() -> r.nextInt(6) + 1)
                    .limit(4)
                    .sorted()
                    .skip(1)
                    .sum();
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