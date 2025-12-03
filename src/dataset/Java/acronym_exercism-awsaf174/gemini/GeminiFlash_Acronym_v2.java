class Acronym {

  private final String acronym;

  Acronym(String phrase) {
    phrase = phrase.replace('-', ' ');
    StringBuilder sb = new StringBuilder();
    boolean nextCap = true;
    for (int i = 0; i < phrase.length(); i++) {
      char c = phrase.charAt(i);
      if (Character.isLetter(c)) {
        if (nextCap) {
          sb.append(Character.toUpperCase(c));
          nextCap = false;
        }
      } else {
        nextCap = true;
      }
    }
    acronym = sb.toString();
  }

  String get() {
    return acronym;
  }
}