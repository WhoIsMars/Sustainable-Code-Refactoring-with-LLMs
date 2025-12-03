import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class WordCount {

    public Map<String, Integer> phrase(String phrase) {
        Map<String, Integer> wordCounts = new HashMap<>();
        StringBuilder cleanedPhrase = new StringBuilder();

        for (char c : phrase.toLowerCase().toCharArray()) {
            if (Character.isLetterOrDigit(c) || c == ' ') {
                cleanedPhrase.append(c);
            } else if (c == '\'') {
                cleanedPhrase.append(c);
            }
        }

        String cleaned = cleanedPhrase.toString().replaceAll(" '|' ", " ").replaceAll("\\s+", " ").trim();

        if (cleaned.isEmpty()) {
            return wordCounts;
        }

        String[] words = cleaned.split(" ");

        for (String word : words) {
            wordCounts.put(word, wordCounts.getOrDefault(word, 0) + 1);
        }

        return wordCounts;
    }
}