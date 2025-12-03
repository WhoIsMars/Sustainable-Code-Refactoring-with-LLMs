import java.util.StringJoiner;

class PigLatinTranslator {

    public static String translate(String input) {
        StringJoiner result = new StringJoiner(" ");
        for (String word : input.split(" ")) {
            if (word.matches("^(?:[aeiou]|yt|xr).*")) {
                result.add(word + "ay");
            } else {
                int splitIndex = word.indexOf('y') > 0 ? word.indexOf('y') : findConsonantClusterEnd(word);
                result.add(word.substring(splitIndex) + word.substring(0, splitIndex) + "ay");
            }
        }
        return result.toString();
    }

    private static int findConsonantClusterEnd(String word) {
        if (word.startsWith("thr") || word.startsWith("sch")) return 3;
        if (word.startsWith("th") || word.startsWith("ch") || word.startsWith("qu")) return 2;
        if (word.startsWith("squ")) return 3;
        return 1;
    }
}