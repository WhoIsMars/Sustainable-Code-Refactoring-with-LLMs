class Acronym {

  private final String acronym;

  Acronym(String phrase) {
    StringBuilder result = new StringBuilder();
    boolean addNext = true;

    for (char c : phrase.toCharArray()) {
      if (Character.isLetterOrDigit(c)) {
        if (addNext) {
          result.append(Character.toUpperCase(c));
          addNext = false;
        }
      } else {
        addNext = true;
      }
    }

    this.acronym = result.toString();
  }

  String get() {
    return acronym;
  }

}