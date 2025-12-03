import java.util.HashMap;
import java.util.Map;

public class WordCount {

  private final Map<String, Integer> wordCount = new HashMap<>();

  public Map<String, Integer> phrase(String phrase) {
    if (phrase == null || phrase.isEmpty()) {
      return wordCount;
    }

    String cleanedPhrase = phrase.toLowerCase().replaceAll("[^a-z0-9\\s]", " ").replaceAll("\\s+", " ").trim();

    if (cleanedPhrase.isEmpty()) {
        return wordCount;
    }

    String[] words = cleanedPhrase.split("\\s");

    for (String word : words) {
      if (!word.isEmpty()) {
        wordCount.merge(word, 1, Integer::sum);
      }
    }

    return wordCount;
  }
}