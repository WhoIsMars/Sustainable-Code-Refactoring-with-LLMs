import java.util.HashMap;
import java.util.Map;

public class WordCount {

    public Map<String, Integer> phrase(String phrase) {
        if (phrase == null || phrase.isEmpty()) {
            return Map.of();
        }

        Map<String, Integer> wordCounts = new HashMap<>();
        StringBuilder word = new StringBuilder();
        int length = phrase.length();

        for (int i = 0; i < length; i++) {
            char c = Character.toLowerCase(phrase.charAt(i));
            if (Character.isLetterOrDigit(c)) {
                word.append(c);
            } else if (c == ' ' || word.length() > 0) {
                if (word.length() > 0) {
                    wordCounts.merge(word.toString(), 1, Integer::sum);
                    word.setLength(0);
                }
            }
        }

        if (word.length() > 0) {
            wordCounts.merge(word.toString(), 1, Integer::sum);
        }

        return wordCounts;
    }
}