import java.util.HashMap;
import java.util.Map;

public class WordCount {

    public Map<String, Integer> phrase(String phrase) {
        Map<String, Integer> wordCounts = new HashMap<>();
        StringBuilder cleanedPhrase = new StringBuilder();

        for (int i = 0; i < phrase.length(); i++) {
            char c = phrase.charAt(i);
            if (Character.isLetterOrDigit(c) || c == '\'') {
                cleanedPhrase.append(Character.toLowerCase(c));
            } else {
                cleanedPhrase.append(' ');
            }
        }

        String cleaned = cleanedPhrase.toString().replaceAll("\\s+", " ").trim();

        if (cleaned.isEmpty()) {
            return wordCounts;
        }

        String[] words = cleaned.split(" ");

        for (String word : words) {
            String trimmedWord = word.replaceFirst("^'+|'+$", "");
            if (!trimmedWord.isEmpty()) {
                wordCounts.put(trimmedWord, wordCounts.getOrDefault(trimmedWord, 0) + 1);
            }
        }

        return wordCounts;
    }
}