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
    char firstChar = word.charAt(0);
    if (isVowel(firstChar) || word.startsWith("yt") || word.startsWith("xr")) {
      return word + "ay";
    }
    if (word.startsWith("thr") || word.startsWith("sch") || word.startsWith("qu")) {
      return word.substring(3) + word.substring(0, 3) + "ay";
    }
    if (word.startsWith("ch") || word.startsWith("th") || word.startsWith("rh")) {
      return word.substring(2) + word.substring(0, 2) + "ay";
    }
    return word.substring(1) + firstChar + "ay";
  }

  private boolean isVowel(char c) {
    switch (c) {
      case 'a': case 'e': case 'i': case 'o': case 'u':
        return true;
      default:
        return false;
    }
  }
}