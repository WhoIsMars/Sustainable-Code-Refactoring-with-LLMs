class Acronym {

  private final String acronym;

  Acronym(String phrase) {
    StringBuilder result = new StringBuilder();
    boolean previousWasSpace = true;

    for (int i = 0; i < phrase.length(); i++) {
      char currentChar = phrase.charAt(i);

      if (Character.isLetter(currentChar)) {
        if (previousWasSpace) {
          result.append(Character.toUpperCase(currentChar));
          previousWasSpace = false;
        }
      } else if (!Character.isLetterOrDigit(currentChar)) {
        previousWasSpace = true;
      } else {
        previousWasSpace = false;
      }

      if (currentChar == ' ' || currentChar == '-') {
        previousWasSpace = true;
      }
    }

    this.acronym = result.toString();
  }

  String get() {
    return acronym;
  }
}