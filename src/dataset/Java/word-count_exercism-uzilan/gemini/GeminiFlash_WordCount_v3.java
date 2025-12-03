import java.util.HashMap;
import java.util.Map;

public class WordCount {

    public Map<String, Integer> phrase(String phrase) {

        String cleaned = phrase.toLowerCase();
        StringBuilder sb = new StringBuilder(cleaned.length());

        for (int i = 0; i < cleaned.length(); i++) {
            char c = cleaned.charAt(i);
            if (Character.isLetterOrDigit(c) || c == ' ') {
                sb.append(c);
            } else if (c == '\'') {
                if (i > 0 && i < cleaned.length() - 1 && Character.isLetterOrDigit(cleaned.charAt(i - 1)) && Character.isLetterOrDigit(cleaned.charAt(i + 1))) {
                    sb.append(c);
                }
            }
        }

        cleaned = sb.toString().replaceAll("\\s+", " ").trim();

        Map<String, Integer> wordCounts = new HashMap<>();
        if (cleaned.isEmpty()) {
            return wordCounts;
        }

        String[] words = cleaned.split(" ");
        for (String word : words) {
            wordCounts.compute(word, (k, v) -> (v == null) ? 1 : v + 1);
        }

        return wordCounts;
    }
}