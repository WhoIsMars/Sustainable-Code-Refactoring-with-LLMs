import java.util.HashMap;
import java.util.Map;

public class WordCount {

    public Map<String, Integer> phrase(String phrase) {
        Map<String, Integer> wordCounts = new HashMap<>();
        StringBuilder cleanedPhrase = new StringBuilder();

        for (int i = 0; i < phrase.length(); i++) {
            char c = phrase.charAt(i);
            if (Character.isLetterOrDigit(c) || c == ' ') {
                cleanedPhrase.append(c);
            } else if (c == '\'') {
                if (i > 0 && i < phrase.length() - 1 && Character.isLetterOrDigit(phrase.charAt(i - 1)) && Character.isLetterOrDigit(phrase.charAt(i + 1))) {
                    cleanedPhrase.append(c);
                }
            }
        }

        String cleaned = cleanedPhrase.toString().toLowerCase().trim();
        String[] words = cleaned.split("\\s+");

        for (String word : words) {
            if (!word.isEmpty()) {
                wordCounts.put(word, wordCounts.getOrDefault(word, 0) + 1);
            }
        }

        return wordCounts;
    }
}