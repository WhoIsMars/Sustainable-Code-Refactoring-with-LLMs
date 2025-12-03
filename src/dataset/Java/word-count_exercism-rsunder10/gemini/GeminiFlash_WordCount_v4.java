import java.util.HashMap;
import java.util.Map;

public class WordCount {

  private final Map<String, Integer> wordCount = new HashMap<>();

  public Map<String, Integer> phrase(String word) {
    String cleanedWord = word.toLowerCase().replaceAll("[^a-z0-9\\s]", " ").replaceAll("\\s+", " ").trim();
    if (cleanedWord.isEmpty()) {
      return wordCount;
    }

    String[] words = cleanedWord.split("\\s");
    for (String eachWord : words) {
      if (!eachWord.isEmpty()) {
        wordCount.compute(eachWord, (k, v) -> (v == null) ? 1 : v + 1);
      }
    }
    return wordCount;
  }
}