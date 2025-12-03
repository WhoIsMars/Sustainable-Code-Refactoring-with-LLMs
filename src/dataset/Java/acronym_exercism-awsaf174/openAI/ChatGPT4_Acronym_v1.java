class Acronym {

  private final String acronym;

  Acronym(String phrase) {
    StringBuilder result = new StringBuilder();
    boolean addNextChar = true;

    for (char c : phrase.toCharArray()) {
      if (Character.isLetterOrDigit(c)) {
        if (addNextChar) {
          result.append(Character.toUpperCase(c));
          addNextChar = false;
        }
      } else {
        addNextChar = true;
      }
    }

    this.acronym = result.toString();
  }

  String get() {
    return acronym;
  }

}