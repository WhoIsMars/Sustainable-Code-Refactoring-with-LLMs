import java.util.regex.Matcher;
import java.util.regex.Pattern;

class PigLatinTranslator{
    
    private static final Pattern VOWEL_PATTERN = Pattern.compile("^([aeiou]|yt|xr).*");
    private static final Pattern CONS_PATTERN = Pattern.compile("^([^aeiou]+)y.*|^(thr?|s?ch|[^aeiou]?qu|[^aeiou]).*");
    
    public static String translate(String input){
        if (input == null || input.isEmpty()) {
            return input;
        }
        
        String[] words = input.split(" ");
        StringBuilder result = new StringBuilder(input.length() + words.length * 2);
        
        for (int i = 0; i < words.length; i++) {
            if (i > 0) {
                result.append(' ');
            }
            
            String word = words[i];
            if (word.isEmpty()) {
                continue;
            }
            
            Matcher vowelMatcher = VOWEL_PATTERN.matcher(word);
            if (vowelMatcher.matches()) {
                result.append(word).append("ay");
            } else {
                Matcher consMatcher = CONS_PATTERN.matcher(word);
                if (consMatcher.matches()) {
                    String consonantGroup = consMatcher.group(1) != null ? consMatcher.group(1) : consMatcher.group(2);
                    result.append(word.substring(consonantGroup.length())).append(consonantGroup).append("ay");
                } else {
                    result.append(word).append("ay");
                }
            }
        }
        
        return result.toString();
    }
}