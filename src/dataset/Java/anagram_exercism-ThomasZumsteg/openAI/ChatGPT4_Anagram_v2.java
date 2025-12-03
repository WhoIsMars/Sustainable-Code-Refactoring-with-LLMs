import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;
import java.util.Map;

public class Anagram {
    private final String anagram;
    private final Map<Character, Integer> anagramCharCount;

    public Anagram(String anagram) {
        this.anagram = anagram.toLowerCase();
        this.anagramCharCount = getCharCount(this.anagram);
    }

    public List<String> match(List<String> words) {
        List<String> anagrams = new ArrayList<>();

        for (String word : words) {
            String wordLower = word.toLowerCase();
            if (!wordLower.equals(anagram) && isAnagram(wordLower)) {
                anagrams.add(word);
            }
        }
        return anagrams;
    }

    private boolean isAnagram(String word) {
        return anagramCharCount.equals(getCharCount(word));
    }

    private Map<Character, Integer> getCharCount(String word) {
        Map<Character, Integer> charCount = new HashMap<>();
        for (char c : word.toCharArray()) {
            charCount.put(c, charCount.getOrDefault(c, 0) + 1);
        }
        return charCount;
    }
}