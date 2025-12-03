import java.util.regex.Pattern;

class PigLatinTranslator {

    private static final Pattern VOWEL_PATTERN = Pattern.compile("^(?:[aeiou]|yt|xr).*");
    private static final Pattern CONSONANT_PATTERN = Pattern.compile("^(?:([^aeiou]+)y.*|(?:thr?|s?ch|[^aeiou]?qu|[^aeiou]).*)");

    public static String translate(String input) {
        String[] words = input.split(" ");
        StringBuilder result = new StringBuilder(input.length() + words.length * 2);

        for (String word : words) {
            if (VOWEL_PATTERN.matcher(word).matches()) {
                result.append(word).append("ay");
            } else {
                var matcher = CONSONANT_PATTERN.matcher(word);
                if (matcher.matches()) {
                    String prefix = matcher.group(1) != null ? matcher.group(1) : matcher.group(0);
                    result.append(word.substring(prefix.length())).append(prefix).append("ay");
                }
            }
            result.append(' ');
        }

        return result.toString().trim();
    }
}