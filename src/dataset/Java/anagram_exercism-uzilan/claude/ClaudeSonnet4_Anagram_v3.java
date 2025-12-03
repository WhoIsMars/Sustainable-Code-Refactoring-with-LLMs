import java.util.List;
import java.util.Map;
import java.util.HashMap;
import java.util.ArrayList;

public class Anagram {

    private final String string;
    private final String normalizedString;
    private final Map<Integer, Integer> map;

    public Anagram(String string) {
        this.string = string;
        this.normalizedString = string.toLowerCase();
        this.map = getWordMap(this.normalizedString);
    }

    public List<String> match(List<String> strings) {
        List<String> result = new ArrayList<>();
        for (String word : strings) {
            if (!word.equalsIgnoreCase(string)) {
                String normalizedWord = word.toLowerCase();
                if (normalizedWord.length() == normalizedString.length() && 
                    getWordMap(normalizedWord).equals(map)) {
                    result.add(word);
                }
            }
        }
        return result;
    }

    private Map<Integer, Integer> getWordMap(String word) {
        Map<Integer, Integer> charCount = new HashMap<>();
        for (int i = 0; i < word.length(); i++) {
            int codePoint = word.codePointAt(i);
            charCount.merge(codePoint, 1, Integer::sum);
            if (Character.charCount(codePoint) == 2) {
                i++;
            }
        }
        return charCount;
    }
}