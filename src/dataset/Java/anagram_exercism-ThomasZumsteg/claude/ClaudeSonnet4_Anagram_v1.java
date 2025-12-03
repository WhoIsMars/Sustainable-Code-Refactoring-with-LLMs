import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

public class Anagram {
    private final String anagram;
    private final String anagramLower;
    private final char[] anagramSorted;

    public Anagram(String anagram) {
        this.anagram = anagram;
        this.anagramLower = anagram.toLowerCase();
        this.anagramSorted = this.anagramLower.toCharArray();
        Arrays.sort(this.anagramSorted);
    }

    public List<String> match(List<String> words) {
        List<String> anagrams = new ArrayList<>(words.size());

        for(String word: words) {
            if (word.length() != anagram.length()) {
                continue;
            }
            
            String wordLower = word.toLowerCase();
            
            if (anagramLower.equals(wordLower)) {
                continue;
            }
            
            char[] wordLetters = wordLower.toCharArray();
            Arrays.sort(wordLetters);

            if(Arrays.equals(anagramSorted, wordLetters)) {
                anagrams.add(word);
            }
        }
        return anagrams;
    }
}