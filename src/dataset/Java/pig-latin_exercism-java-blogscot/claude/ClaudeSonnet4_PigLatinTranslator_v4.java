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
    char secondChar = word.length() > 1 ? word.charAt(1) : '\0';
    char thirdChar = word.length() > 2 ? word.charAt(2) : '\0';
    
    if (isVowel(firstChar) || (firstChar == 'y' && secondChar == 't') || (firstChar == 'x' && secondChar == 'r')) {
      return word + "ay";
    }
    
    if ((firstChar == 't' && secondChar == 'h' && thirdChar == 'r') ||
        (firstChar == 's' && secondChar == 'c' && thirdChar == 'h') ||
        (firstChar == 'q' && secondChar == 'u' && !isVowel(firstChar))) {
      return word.substring(3) + word.substring(0, 3) + "ay";
    }
    
    if ((firstChar == 'c' && secondChar == 'h') ||
        (firstChar == 'q' && secondChar == 'u') ||
        (firstChar == 't' && secondChar == 'h') ||
        (firstChar == 'r' && secondChar == 'h')) {
      return word.substring(2) + word.substring(0, 2) + "ay";
    }
    
    return word.substring(1) + firstChar + "ay";
  }

  private boolean isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
  }
}