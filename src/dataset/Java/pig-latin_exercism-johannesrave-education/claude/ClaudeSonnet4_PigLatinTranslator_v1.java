import java.util.regex.Pattern;

class PigLatinTranslator{
    
    private static final Pattern VOWEL_PATTERN = Pattern.compile("^([aeiou]|yt|xr)");
    private static final Pattern CONS_PATTERN = Pattern.compile("^([^aeiou]+)y|^(thr?|s?ch|[^aeiou]?qu|[^aeiou])");
    
    public static String translate(String input){
        String[] words = input.split(" ");
        StringBuilder result = new StringBuilder();
        
        for (int i = 0; i < words.length; i++) {
            if (i > 0) {
                result.append(" ");
            }
            
            String word = words[i];
            
            if (VOWEL_PATTERN.matcher(word).find()) {
                result.append(word).append("ay");
            } else {
                var consMatcher = CONS_PATTERN.matcher(word);
                if (consMatcher.find()) {
                    String consonantGroup = consMatcher.group(1) != null ? consMatcher.group(1) : consMatcher.group(2);
                    int groupStart = consMatcher.group(1) != null ? consMatcher.start(1) : consMatcher.start(2);
                    int groupEnd = consMatcher.group(1) != null ? consMatcher.end(1) : consMatcher.end(2);
                    
                    result.append(word.substring(groupEnd))
                          .append(consonantGroup)
                          .append("ay");
                } else {
                    result.append(word).append("ay");
                }
            }
        }
        
        return result.toString();
    }
}