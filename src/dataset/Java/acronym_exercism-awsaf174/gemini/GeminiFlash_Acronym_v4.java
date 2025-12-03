class Acronym {

  private final String acronym;

  Acronym(String phrase) {
    StringBuilder result = new StringBuilder();
    phrase = phrase.replace('-', ' ');
    phrase = phrase.replaceAll("[^A-Za-z0-9\\s]", "");
    phrase = phrase.replaceAll("\\s+", " ");
    phrase = phrase.trim();

    if (phrase.isEmpty()) {
      acronym = "";
      return;
    }

    result.append(Character.toUpperCase(phrase.charAt(0)));

    int phraseLength = phrase.length();
    for (int i = 1; i < phraseLength; i++) {
      if (phrase.charAt(i) == ' ') {
        if (i + 1 < phraseLength) {
          result.append(Character.toUpperCase(phrase.charAt(i + 1)));
          i++;
        }
      }
    }

    acronym = result.toString();
  }

  String get() {
    return acronym;
  }
}