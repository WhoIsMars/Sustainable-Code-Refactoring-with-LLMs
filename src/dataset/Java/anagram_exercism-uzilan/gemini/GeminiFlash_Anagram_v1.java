import java.util.List;
import java.util.Arrays;
import java.util.stream.Collectors;

public class Anagram {

    private final String string;
    private final int[] charCounts;
    private final int stringLength;

    public Anagram(String string) {
        this.string = string;
        this.stringLength = string.length();
        this.charCounts = getCharacterCounts(string);
    }

    public List<String> match(List<String> strings) {
        return strings.stream()
                .filter(word -> !word.equalsIgnoreCase(string) && word.length() == stringLength && areAnagrams(word))
                .collect(Collectors.toList());
    }

    private boolean areAnagrams(String word) {
        int[] wordCounts = getCharacterCounts(word);
        return Arrays.equals(charCounts, wordCounts);
    }

    private int[] getCharacterCounts(String word) {
        int[] counts = new int[26];
        word = word.toLowerCase();
        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);
            if (c >= 'a' && c <= 'z') {
                counts[c - 'a']++;
            }
        }
        return counts;
    }
}