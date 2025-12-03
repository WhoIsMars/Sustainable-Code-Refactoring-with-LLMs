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
    
    // Check vowel first (most common case)
    if (isVowel(firstChar)) return word + "ay";
    
    // Check special starting patterns
    if (word.length() >= 2) {
      char secondChar = word.charAt(1);
      
      // Two-character prefixes
      if (firstChar == 'y' && secondChar == 't') return word + "ay";
      if (firstChar == 'x' && secondChar == 'r') return word + "ay";
      if (firstChar == 'c' && secondChar == 'h') return word.substring(2) + word.substring(0, 2) + "ay";
      if (firstChar == 'q' && secondChar == 'u') return word.substring(2) + word.substring(0, 2) + "ay";
      if (firstChar == 't' && secondChar == 'h') return word.substring(2) + word.substring(0, 2) + "ay";
      if (firstChar == 'r' && secondChar == 'h') return word.substring(2) + word.substring(0, 2) + "ay";
      
      // Three-character prefixes
      if (word.length() >= 3) {
        char thirdChar = word.charAt(2);
        if (firstChar == 't' && secondChar == 'h' && thirdChar == 'r') return word.substring(3) + word.substring(0, 3) + "ay";
        if (firstChar == 's' && secondChar == 'c' && thirdChar == 'h') return word.substring(3) + word.substring(0, 3) + "ay";
        if (firstChar == 'q' && secondChar == 'u' && !isVowel(firstChar)) return word.substring(3) + word.substring(0, 3) + "ay";
      }
    }
    
    // Default case: move first consonant
    return word.substring(1) + firstChar + "ay";
  }

  private boolean isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
  }
}