import java.util.StringJoiner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class PigLatinTranslator {

    private static final Pattern VOWEL_START = Pattern.compile("^([aeiou]|yt|xr).*");
    private static final Pattern CONSONANT_START = Pattern.compile("^([^aeiou]+)y.*|^(thr?|s?ch|[^aeiou]?qu|[^aeiou]).*");

    public static String translate(String input) {
        StringJoiner result = new StringJoiner(" ");
        for (String word : input.split(" ")) {
            String pigLatinWord = translateWord(word);
            result.add(pigLatinWord);
        }
        return result.toString();
    }

    private static String translateWord(String word) {
        Matcher vowelMatcher = VOWEL_START.matcher(word);
        if (vowelMatcher.matches()) {
            return word + "ay";
        }

        Matcher consonantMatcher = CONSONANT_START.matcher(word);
        if (consonantMatcher.matches()) {
            int group = (consonantMatcher.group(1) == null) ? 2 : 1;
            String consonantCluster = consonantMatcher.group(group);
            return word.substring(consonantCluster.length()) + consonantCluster + "ay";
        }

        return word + "ay"; // Default case, though should not happen with the problem constraints
    }
}