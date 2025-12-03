import java.util.HashMap;
import java.util.Map;

public class WordCount {

    public Map<String, Integer> phrase(String phrase) {
        Map<String, Integer> wordCounts = new HashMap<>();
        if (phrase == null || phrase.isEmpty()) {
            return wordCounts;
        }

        String[] words = phrase.toLowerCase()
                .replaceAll("[,.:!&@$%\\^]", " ")
                .replaceAll(" '|' ", " ")
                .trim()
                .split("\\s+");

        for (String word : words) {
            wordCounts.merge(word, 1, Integer::sum);
        }

        return wordCounts;
    }
}