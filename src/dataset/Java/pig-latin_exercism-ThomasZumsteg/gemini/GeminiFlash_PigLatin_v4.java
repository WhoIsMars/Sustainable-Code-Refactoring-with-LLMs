import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class PigLatin {
    private static final Pattern QU_PATTERN = Pattern.compile("([^aeiouAEIOU]*qu)(.*)");
    private static final Pattern Y_PATTERN = Pattern.compile("^y[^aeiouAEIOU]");
    private static final Pattern DEFAULT_PATTERN = Pattern.compile("([^aeiouAEIOU]*)([aeiouAEIOU].*)");

    public static String translate(String input) {
        return Stream.of(input.split(" "))
            .map(PigLatin::translateWord)
            .collect(Collectors.joining(" "));
    }

    private static String translateWord(String input) {
        Matcher quMatch = QU_PATTERN.matcher(input);
        if (quMatch.find()) {
            return quMatch.group(2) + quMatch.group(1) + "ay";
        }

        if (Y_PATTERN.matcher(input).find()) {
            return input + "ay";
        }

        Matcher defaultMatch = DEFAULT_PATTERN.matcher(input);
        if (defaultMatch.find()) {
            return defaultMatch.group(2) + defaultMatch.group(1) + "ay";
        }

        return input + "ay";
    }
}