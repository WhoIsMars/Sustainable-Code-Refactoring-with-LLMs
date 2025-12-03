import java.util.Arrays;
import java.util.stream.Collectors;

public class PigLatinTranslator {

    public String translate(String string) {
        return Arrays.stream(string.split(" "))
                .map(s -> aLotOfRegexMagic(s) + "ay")
                .collect(Collectors.joining(" "));
    }

    private String aLotOfRegexMagic(String s) {
        if (s.isEmpty()) {
            return s;
        }
        
        char first = s.charAt(0);
        char second = s.length() > 1 ? s.charAt(1) : '\0';
        char third = s.length() > 2 ? s.charAt(2) : '\0';
        
        // Check for vowel sounds at start
        if (isVowel(first) || (first == 'y' && second == 't') || (first == 'x' && second == 'r')) {
            return s;
        }
        
        // Check for 3-letter consonant clusters
        if (first == 't' && second == 'h' && third == 'r') {
            return rotate(s, 3);
        }
        if (first == 's' && second == 'c' && third == 'h') {
            return rotate(s, 3);
        }
        if (isConsonant(first) && second == 'q' && third == 'u') {
            return rotate(s, 3);
        }
        
        // Check for 2-letter combinations
        if ((first == 'c' && second == 'h') || 
            (first == 'q' && second == 'u') || 
            (first == 't' && second == 'h')) {
            return rotate(s, 2);
        }
        
        // Check for consonant cluster followed by 'y'
        if (s.length() >= 3 && isConsonant(first) && isConsonant(second) && third == 'y') {
            return rotate(s, 2);
        }
        
        return rotate(s, 1);
    }
    
    private boolean isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
    
    private boolean isConsonant(char c) {
        return c >= 'a' && c <= 'z' && !isVowel(c);
    }

    private String rotate(String s, int i) {
        return s.substring(i) + s.substring(0, i);
    }
}