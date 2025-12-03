import java.util.HashMap;
import java.util.Map;

public class WordCount {

    public Map<String, Integer> phrase(String phrase) {
        Map<String, Integer> wordCounts = new HashMap<>();
        StringBuilder word = new StringBuilder();
        phrase = phrase.toLowerCase();

        for (char c : phrase.toCharArray()) {
            if (Character.isLetterOrDigit(c)) {
                word.append(c);
            } else if (word.length() > 0) {
                wordCounts.merge(word.toString(), 1, Integer::sum);
                word.setLength(0);
            }
        }

        if (word.length() > 0) {
            wordCounts.merge(word.toString(), 1, Integer::sum);
        }

        return wordCounts;
    }
}