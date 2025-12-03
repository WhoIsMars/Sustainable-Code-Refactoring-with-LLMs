class PigLatinTranslator {

    private static final Pattern VOWEL_PATTERN = Pattern.compile("^(?:[aeiou]|yt|xr).*");
    private static final Pattern CONS_PATTERN = Pattern.compile("^(?:([^aeiou]+)y.*|(?:thr?|s?ch|[^aeiou]?qu|[^aeiou]).*)");

    public static String translate(String input) {
        StringBuilder result = new StringBuilder();
        String[] words = input.split(" ");

        for (String word : words) {
            if (VOWEL_PATTERN.matcher(word).matches()) {
                result.append(word).append("ay");
            } else {
                Matcher consMatcher = CONS_PATTERN.matcher(word);
                if (consMatcher.matches()) {
                    String prefix = consMatcher.group(1) != null ? consMatcher.group(1) : consMatcher.group(0).substring(0, consMatcher.end(0));
                    result.append(word.substring(prefix.length())).append(prefix).append("ay");
                }
            }
            result.append(" ");
        }

        return result.toString().trim();
    }
}