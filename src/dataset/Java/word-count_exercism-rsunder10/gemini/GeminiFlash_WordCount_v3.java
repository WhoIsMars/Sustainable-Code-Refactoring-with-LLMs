import java.util.HashMap;
import java.util.Map;

public class WordCount {

  private final Map<String, Integer> wordCount = new HashMap<>();

  public Map<String, Integer> phrase(String word) {
    String cleanedWord = word.replaceAll("[^A-Za-z0-9]", " ").replaceAll("\\s+", " ").trim();
    if (cleanedWord.isEmpty()) {
      return wordCount;
    }

    for (String eachWord : cleanedWord.split("\\s")) {
      String lowerCaseWord = eachWord.toLowerCase();
      wordCount.compute(lowerCaseWord, (k, v) -> (v == null) ? 1 : v + 1);
    }
    return wordCount;
  }
}