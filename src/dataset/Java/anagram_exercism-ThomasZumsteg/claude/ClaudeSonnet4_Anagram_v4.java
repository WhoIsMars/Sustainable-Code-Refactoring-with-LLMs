import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

public class Anagram {
    private final String anagramLower;
    private final char[] anagramSorted;

    public Anagram(String anagram) {
        this.anagramLower = anagram.toLowerCase();
        this.anagramSorted = this.anagramLower.toCharArray();
        Arrays.sort(this.anagramSorted);
    }

    public List<String> match(List<String> words) {
        List<String> anagrams = new ArrayList<>(words.size());

        for (String word : words) {
            String wordLower = word.toLowerCase();
            
            if (anagramLower.length() != wordLower.length() || anagramLower.equals(wordLower)) {
                continue;
            }
            
            char[] wordSorted = wordLower.toCharArray();
            Arrays.sort(wordSorted);

            if (Arrays.equals(anagramSorted, wordSorted)) {
                anagrams.add(word);
            }
        }
        return anagrams;
    }
}