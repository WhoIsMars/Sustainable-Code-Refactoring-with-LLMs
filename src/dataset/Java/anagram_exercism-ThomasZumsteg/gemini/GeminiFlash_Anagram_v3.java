import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

public class Anagram {
    private final String anagramLower;
    private final char[] anagramLetters;

    public Anagram(String anagram) {
        this.anagramLower = anagram.toLowerCase();
        this.anagramLetters = this.anagramLower.toCharArray();
        Arrays.sort(this.anagramLetters);
    }

    public List<String> match(List<String> words) {
        List<String> anagrams = new ArrayList<>();
        for (String word : words) {
            if (isAnagram(word)) {
                anagrams.add(word);
            }
        }
        return anagrams;
    }

    private boolean isAnagram(String word) {
        String wordLower = word.toLowerCase();

        if (anagramLower.equals(wordLower)) {
            return false;
        }

        if (wordLower.length() != anagramLower.length()) {
            return false;
        }

        char[] wordLetters = wordLower.toCharArray();
        Arrays.sort(wordLetters);

        return Arrays.equals(anagramLetters, wordLetters);
    }
}