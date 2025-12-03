import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Anagram {
    private final String anagram;
    private final String sortedAnagram;

    public Anagram(String anagram) {
        this.anagram = anagram;
        this.sortedAnagram = sortString(anagram.toLowerCase());
    }

    private String sortString(String str) {
        char[] chars = str.toCharArray();
        Arrays.sort(chars);
        return new String(chars);
    }

    public List<String> match(List<String> words) {
        List<String> anagrams = new ArrayList<>();
        String anagramLower = this.anagram.toLowerCase();

        for (String word : words) {
            String wordLower = word.toLowerCase();

            if (wordLower.length() != anagramLower.length() || anagramLower.equals(wordLower)) {
                continue;
            }

            if (sortedAnagram.equals(sortString(wordLower))) {
                anagrams.add(word);
            }
        }
        return anagrams;
    }
}