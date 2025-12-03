import static java.util.Objects.requireNonNull;

class Acronym {
  private final String acronym;

  Acronym(String phrase) {
    requireNonNull(phrase);

    StringBuilder result = new StringBuilder();
    boolean newWord = true;
    for (char c : phrase.toCharArray()) {
      if (Character.isLetter(c)) {
        if (newWord) {
          result.append(Character.toUpperCase(c));
          newWord = false;
        }
      } else {
        newWord = c != '\'';
      }
    }
    acronym = result.toString();
  }

  String getAcronym() {
    return acronym;
  }
}