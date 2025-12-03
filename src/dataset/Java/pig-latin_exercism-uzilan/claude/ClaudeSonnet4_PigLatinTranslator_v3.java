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
        
        if (isVowelStart(first, second)) {
            return s;
        }
        
        if (isThreeCharPattern(first, second, third)) {
            return rotate(s, 3);
        }
        
        if (isTwoCharPattern(s, first, second)) {
            return rotate(s, 2);
        }
        
        return rotate(s, 1);
    }
    
    private boolean isVowelStart(char first, char second) {
        return first == 'a' || first == 'e' || first == 'i' || first == 'o' || first == 'u' ||
               (first == 'y' && second == 't') || (first == 'x' && second == 'r');
    }
    
    private boolean isThreeCharPattern(char first, char second, char third) {
        return (first == 't' && second == 'h' && third == 'r') ||
               (first == 's' && second == 'c' && third == 'h') ||
               (isConsonant(first) && second == 'q' && third == 'u');
    }
    
    private boolean isTwoCharPattern(String s, char first, char second) {
        if ((first == 'c' && second == 'h') || 
            (first == 'q' && second == 'u') || 
            (first == 't' && second == 'h')) {
            return true;
        }
        
        if (s.length() >= 3 && isConsonant(first) && isConsonant(second) && s.charAt(2) == 'y') {
            return true;
        }
        
        return false;
    }
    
    private boolean isConsonant(char c) {
        return c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != '\0';
    }

    private String rotate(String s, int i) {
        return s.substring(i) + s.substring(0, i);
    }
}