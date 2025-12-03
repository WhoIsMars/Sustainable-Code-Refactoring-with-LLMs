import java.util.HashMap;
import java.util.Map;

public class WordCount {

  public Map<String, Integer> wordCount = new HashMap<>();

  public Map<String, Integer> phrase(String word) {
    if (word == null || word.isEmpty()) {
      return wordCount;
    }
    
    StringBuilder cleanWord = new StringBuilder(word.length());
    boolean lastWasSpace = false;
    
    for (int i = 0; i < word.length(); i++) {
      char c = word.charAt(i);
      if (Character.isLetterOrDigit(c)) {
        cleanWord.append(Character.toLowerCase(c));
        lastWasSpace = false;
      } else if (!lastWasSpace && cleanWord.length() > 0) {
        cleanWord.append(' ');
        lastWasSpace = true;
      }
    }
    
    if (cleanWord.length() == 0) {
      return wordCount;
    }
    
    if (lastWasSpace) {
      cleanWord.setLength(cleanWord.length() - 1);
    }
    
    int start = 0;
    for (int i = 0; i <= cleanWord.length(); i++) {
      if (i == cleanWord.length() || cleanWord.charAt(i) == ' ') {
        if (i > start) {
          String token = cleanWord.substring(start, i);
          wordCount.merge(token, 1, Integer::sum);
        }
        start = i + 1;
      }
    }
    
    return wordCount;
  }
}