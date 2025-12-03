import java.util.HashMap;
import java.util.Map;

public class WordCount {

  private final Map<String, Integer> wordCount = new HashMap<>();

  public Map<String, Integer> phrase(String word) {
    if (word == null || word.isEmpty()) {
      return wordCount;
    }

    String[] words = word.toLowerCase().replaceAll("[^a-z0-9\\s]", " ").split("\\s+");
    for (String eachWord : words) {
      if (!eachWord.isEmpty()) {
        wordCount.merge(eachWord, 1, Integer::sum);
      }
    }
    return wordCount;
  }
}