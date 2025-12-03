class Acronym {

  private final String acronym;

  Acronym(String phrase) {
    if (phrase == null || phrase.isEmpty()) {
      acronym = "";
      return;
    }

    StringBuilder result = new StringBuilder();
    boolean nextIsAcronym = true;
    
    for (int i = 0; i < phrase.length(); i++) {
      char c = phrase.charAt(i);
      
      if (Character.isLetter(c) || Character.isDigit(c)) {
        if (nextIsAcronym) {
          result.append(Character.toUpperCase(c));
          nextIsAcronym = false;
        }
      } else {
        nextIsAcronym = true;
      }
    }
    
    acronym = result.toString();
  }

  String get() {
    return acronym;
  }
}