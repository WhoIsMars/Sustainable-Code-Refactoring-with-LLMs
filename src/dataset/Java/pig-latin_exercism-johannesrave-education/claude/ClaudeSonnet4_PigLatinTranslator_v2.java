import java.util.StringJoiner;

class PigLatinTranslator{
    
    private static final String VOWEL_PATTERN = "^([aeiou]|yt|xr)";
    private static final String CONSONANT_PATTERN = "^([^aeiou]+)y|^(thr?|s?ch|[^aeiou]?qu|[^aeiou])";
    
    public static String translate(String input){
        StringJoiner result = new StringJoiner(" ");
        String[] words = input.split(" ");
        
        for (String word : words) {
            if (word.isEmpty()) {
                result.add(word);
                continue;
            }
            
            StringBuilder sb = new StringBuilder(word.length() + 2);
            
            if (startsWithVowelSound(word)) {
                sb.append(word).append("ay");
            } else {
                int consonantEnd = findConsonantClusterEnd(word);
                sb.append(word, consonantEnd, word.length())
                  .append(word, 0, consonantEnd)
                  .append("ay");
            }
            
            result.add(sb);
        }
        
        return result.toString();
    }
    
    private static boolean startsWithVowelSound(String word) {
        if (word.length() == 0) return false;
        char first = word.charAt(0);
        if (first == 'a' || first == 'e' || first == 'i' || first == 'o' || first == 'u') {
            return true;
        }
        return word.startsWith("yt") || word.startsWith("xr");
    }
    
    private static int findConsonantClusterEnd(String word) {
        int len = word.length();
        
        // Handle special cases first
        if (word.startsWith("thr")) return 3;
        if (word.startsWith("th")) return 2;
        if (word.startsWith("sch")) return 3;
        if (word.startsWith("ch")) return 2;
        
        // Handle 'qu' patterns
        if (word.startsWith("qu")) return 2;
        if (len > 2 && word.charAt(1) == 'q' && word.charAt(2) == 'u') return 3;
        
        // Handle consonant + y
        int i = 0;
        while (i < len && !isVowel(word.charAt(i))) {
            i++;
        }
        if (i < len && word.charAt(i) == 'y') {
            return i + 1;
        }
        
        // Single consonant
        return Math.min(1, len);
    }
    
    private static boolean isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
}