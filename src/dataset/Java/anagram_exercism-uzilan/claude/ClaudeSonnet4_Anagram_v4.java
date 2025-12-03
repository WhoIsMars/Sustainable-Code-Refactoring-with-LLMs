import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Anagram {

    private final String string;
    private final int[] charCounts;
    private final String normalizedString;

    public Anagram(String string) {
        this.string = string;
        this.normalizedString = string.toLowerCase();
        this.charCounts = getCharCounts(this.normalizedString);
    }

    public List<String> match(List<String> strings) {
        List<String> result = new ArrayList<>();
        for (String word : strings) {
            if (!word.equalsIgnoreCase(string) && isAnagram(word)) {
                result.add(word);
            }
        }
        return result;
    }

    private boolean isAnagram(String word) {
        String normalizedWord = word.toLowerCase();
        if (normalizedWord.length() != normalizedString.length()) {
            return false;
        }
        return Arrays.equals(charCounts, getCharCounts(normalizedWord));
    }

    private int[] getCharCounts(String word) {
        int[] counts = new int[26];
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            if (c >= 'a' && c <= 'z') {
                counts[c - 'a']++;
            }
        }
        return counts;
    }
}