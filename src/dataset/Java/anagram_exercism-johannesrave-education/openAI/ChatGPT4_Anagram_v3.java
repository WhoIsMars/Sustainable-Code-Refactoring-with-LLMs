import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Anagram {
    private final String base;
    private final Map<Character, Integer> baseCharCount;

    public Anagram(String in) {
        this.base = in.toLowerCase();
        this.baseCharCount = getCharCount(this.base);
    }

    public List<String> match(List<String> candidates) {
        List<String> result = new ArrayList<>();
        for (String candidate : candidates) {
            String lowerCandidate = candidate.toLowerCase();
            if (!base.equals(lowerCandidate) && baseCharCount.equals(getCharCount(lowerCandidate))) {
                result.add(candidate);
            }
        }
        return result;
    }

    private Map<Character, Integer> getCharCount(String str) {
        Map<Character, Integer> charCount = new HashMap<>();
        for (char c : str.toCharArray()) {
            charCount.put(c, charCount.getOrDefault(c, 0) + 1);
        }
        return charCount;
    }
}