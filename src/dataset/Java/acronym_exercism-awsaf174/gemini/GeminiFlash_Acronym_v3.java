class Acronym {

  private final String acronym;

  Acronym(String phrase) {
    StringBuilder result = new StringBuilder();
    phrase = phrase.replace('-', ' ');
    phrase = phrase.replaceAll("[^A-Za-z0-9\\s]", "");
    phrase = phrase.replaceAll("\\s+", " ");
    phrase = phrase.trim();

    if (!phrase.isEmpty()) {
      result.append(Character.toUpperCase(phrase.charAt(0)));

      for (int i = 1; i < phrase.length(); i++) {
        if (Character.isWhitespace(phrase.charAt(i))) {
          if (i + 1 < phrase.length()) {
            result.append(Character.toUpperCase(phrase.charAt(i + 1)));
            i++;
          }
        }
      }
    }
    this.acronym = result.toString();
  }

  String get() {
    return acronym;
  }
}