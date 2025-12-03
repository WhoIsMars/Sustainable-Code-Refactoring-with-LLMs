import java.util.StringJoiner;

class PigLatinTranslator {

  String translate(String phrase) {
    String[] words = phrase.split(" ");
    StringJoiner result = new StringJoiner(" ");
    for (String word : words) {
      result.add(translateWord(word));
    }
    return result.toString();
  }

  private String translateWord(String word) {
    int len = word.length();
    char firstChar = word.charAt(0);

    if (startsWithVowelLike(word)) {
      return word + "ay";
    }

    if (len >= 3 && (word.startsWith("thr") || word.startsWith("sch"))) {
      return word.substring(3) + word.substring(0, 3) + "ay";
    }

    if (len >= 2 && word.startsWith("qu") && !isVowel(firstChar)) {
        return word.substring(2) + word.substring(0, 2) + "ay";
    }

    if (len >= 2 && (word.startsWith("ch") || word.startsWith("th") || word.startsWith("rh"))) {
      return word.substring(2) + word.substring(0, 2) + "ay";
    }

    return word.substring(1) + firstChar + "ay";
  }


  private boolean startsWithVowelLike(String word) {
      char firstChar = word.charAt(0);
      return firstChar == 'a' || firstChar == 'e' || firstChar == 'i' || firstChar == 'o' || firstChar == 'u' || word.startsWith("yt") || word.startsWith("xr");
  }

  private boolean isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
  }
}