import java.util.HashMap;
import java.util.Map;

public class WordCount {
    public Map<String, Integer> phrase(String sentence) {
        Map<String, Integer> wordCounts = new HashMap<>();
        String[] words = sentence.toLowerCase().replaceAll("[^a-z0-9 ]", "").split("\\s+");
        for (String word : words) {
            if (!word.isEmpty()) {
                wordCounts.put(word, wordCounts.getOrDefault(word, 0) + 1);
            }
        }
        return wordCounts;
    }
}