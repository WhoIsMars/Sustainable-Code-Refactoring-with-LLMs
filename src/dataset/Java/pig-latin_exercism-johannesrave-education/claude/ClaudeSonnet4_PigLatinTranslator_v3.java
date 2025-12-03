import java.util.StringJoiner;
import java.util.regex.Pattern;

class PigLatinTranslator{
    
    private static final Pattern VOWEL_PATTERN = Pattern.compile("^([aeiou]|yt|xr)");
    private static final Pattern CONSONANT_PATTERN = Pattern.compile("^(thr?|s?ch|[^aeiou]?qu|[^aeiou]+y|[^aeiou])");
    
    public static String translate(String input){
        String[] words = input.split(" ");
        StringJoiner result = new StringJoiner(" ");
        
        for (String word : words) {
            if (VOWEL_PATTERN.matcher(word).find()) {
                result.add(word + "ay");
            } else {
                var matcher = CONSONANT_PATTERN.matcher(word);
                if (matcher.find()) {
                    String consonantCluster = matcher.group(1);
                    result.add(word.substring(consonantCluster.length()) + consonantCluster + "ay");
                } else {
                    result.add(word + "ay");
                }
            }
        }
        
        return result.toString();
    }
}