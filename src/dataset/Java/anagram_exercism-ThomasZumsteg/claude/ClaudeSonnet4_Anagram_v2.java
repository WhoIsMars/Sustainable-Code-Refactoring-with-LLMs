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
        List<String> anagrams = new ArrayList<String>(words.size());

        for(String word: words) {
            String wordLower = word.toLowerCase();
            
            if (wordLower.length() != anagramLower.length() || anagramLower.equals(wordLower)) {
                continue;
            }
            
            char[] wordLetters = wordLower.toCharArray();
            Arrays.sort(wordLetters);

            if(Arrays.equals(anagramLetters, wordLetters)) {
                anagrams.add(word);
            }
        }
        return anagrams;
    }
}