import java.util.StringJoiner;

public class PigLatinTranslator {

    public String translate(String string) {
        if (string.isEmpty()) {
            return string;
        }
        
        String[] words = string.split(" ");
        StringJoiner result = new StringJoiner(" ");
        
        for (String word : words) {
            result.add(aLotOfRegexMagic(word) + "ay");
        }
        
        return result.toString();
    }

    private String aLotOfRegexMagic(String s) {
        if (s.isEmpty()) {
            return s;
        }
        
        char first = s.charAt(0);
        char second = s.length() > 1 ? s.charAt(1) : '\0';
        char third = s.length() > 2 ? s.charAt(2) : '\0';
        
        // Check for vowel start or special cases (yt, xr)
        if (isVowel(first) || (first == 'y' && second == 't') || (first == 'x' && second == 'r')) {
            return s;
        }
        
        // Check for 3-letter consonant clusters
        if (s.length() >= 3) {
            if ((first == 't' && second == 'h' && third == 'r') ||
                (first == 's' && second == 'c' && third == 'h') ||
                (isConsonant(first) && second == 'q' && third == 'u')) {
                return rotate(s, 3);
            }
        }
        
        // Check for 2-letter patterns
        if (s.length() >= 2) {
            if ((first == 'c' && second == 'h') ||
                (first == 'q' && second == 'u') ||
                (first == 't' && second == 'h') ||
                (isConsonantClusterWithY(s))) {
                return rotate(s, 2);
            }
        }
        
        return rotate(s, 1);
    }
    
    private boolean isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
    
    private boolean isConsonant(char c) {
        return c >= 'a' && c <= 'z' && !isVowel(c);
    }
    
    private boolean isConsonantClusterWithY(String s) {
        if (s.length() < 3) return false;
        
        int consonantCount = 0;
        for (int i = 0; i < s.length() && isConsonant(s.charAt(i)); i++) {
            consonantCount++;
        }
        
        return consonantCount >= 2 && s.charAt(consonantCount) == 'y';
    }

    private String rotate(String s, int i) {
        return s.substring(i) + s.substring(0, i);
    }
}