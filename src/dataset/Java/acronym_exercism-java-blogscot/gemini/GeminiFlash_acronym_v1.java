import static java.util.Objects.requireNonNull;

class Acronym {
  private final String acronym;

  Acronym(String phrase) {
    requireNonNull(phrase);

    StringBuilder result = new StringBuilder();
    boolean firstChar = true;
    for (int i = 0; i < phrase.length(); i++) {
      char c = phrase.charAt(i);
      if (firstChar && Character.isLetter(c)) {
        result.append(Character.toUpperCase(c));
        firstChar = false;
      } else if (!Character.isLetterOrDigit(c)) {
        firstChar = true;
      }
    }
    acronym = result.toString();
  }

  String getAcronym() {
    return acronym;
  }
}