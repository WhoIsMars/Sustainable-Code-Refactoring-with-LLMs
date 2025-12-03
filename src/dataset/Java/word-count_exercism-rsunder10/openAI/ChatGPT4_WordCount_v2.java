import java.util.HashMap;
import java.util.Map;

public class WordCount {

  private final Map<String, Integer> wordCount = new HashMap<>();

  public Map<String, Integer> phrase(String input) {
    if (input == null || input.isEmpty()) return wordCount;

    String[] words = input.toLowerCase().replaceAll("[^a-z0-9\\s]", "").split("\\s+");
    for (String word : words) {
      if (!word.isEmpty()) {
        wordCount.merge(word, 1, Integer::sum);
      }
    }
    return wordCount;
  }
}