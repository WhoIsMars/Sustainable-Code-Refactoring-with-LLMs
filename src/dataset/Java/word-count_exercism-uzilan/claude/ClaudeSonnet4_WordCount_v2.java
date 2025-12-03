import java.util.HashMap;
import java.util.Map;

public class WordCount {

    public Map<String, Integer> phrase(String phrase) {
        if (phrase == null || phrase.isEmpty()) {
            return new HashMap<>();
        }
        
        Map<String, Integer> wordCount = new HashMap<>();
        StringBuilder word = new StringBuilder();
        
        for (int i = 0; i < phrase.length(); i++) {
            char c = phrase.charAt(i);
            
            if (Character.isLetter(c) || Character.isDigit(c)) {
                word.append(Character.toLowerCase(c));
            } else if (c == '\'' && word.length() > 0 && i < phrase.length() - 1 && 
                      (Character.isLetter(phrase.charAt(i + 1)) || Character.isDigit(phrase.charAt(i + 1)))) {
                word.append(c);
            } else if (word.length() > 0) {
                String wordStr = word.toString();
                wordCount.merge(wordStr, 1, Integer::sum);
                word.setLength(0);
            }
        }
        
        if (word.length() > 0) {
            String wordStr = word.toString();
            wordCount.merge(wordStr, 1, Integer::sum);
        }
        
        return wordCount;
    }
}