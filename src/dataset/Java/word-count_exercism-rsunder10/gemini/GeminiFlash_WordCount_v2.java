import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class WordCount {

  public Map<String, Integer> wordCount = new HashMap<>();

  public Map<String, Integer> phrase(String word) {
    String cleanedWord = word.replaceAll("[^A-Za-z0-9\\s]", " ").toLowerCase();
    Arrays.stream(cleanedWord.split("\\s+"))
            .filter(s -> !s.isEmpty())
            .forEach(w -> wordCount.compute(w, (k, v) -> (v == null) ? 1 : v + 1));
    return wordCount;
  }
}