import java.util.Arrays;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

public class PigLatinTranslator {

    private static final Pattern STARTS_WITH_VOWEL = Pattern.compile("^[aeiou].*");
    private static final Pattern STARTS_WITH_YT_XR = Pattern.compile("^(yt|xr).*");
    private static final Pattern STARTS_WITH_THR_SCH_CONSONANT_QU = Pattern.compile("^(thr|sch|[bcdfghjklmnpqrstvwxyz]qu).*");
    private static final Pattern STARTS_WITH_CH_QU_TH_CONSONANT_CLUSTER_Y = Pattern.compile("^(ch|qu|th|([bcdfghjklmnpqrstvwxyz]){2,}y).*");

    public String translate(String string) {
        return Arrays.stream(string.split(" "))
                .map(this::translateWord)
                .collect(Collectors.joining(" "));
    }

    private String translateWord(String s) {
        if (STARTS_WITH_VOWEL.matcher(s).matches() || STARTS_WITH_YT_XR.matcher(s).matches()) {
            return s + "ay";
        }
        if (STARTS_WITH_THR_SCH_CONSONANT_QU.matcher(s).matches()) {
            return rotate(s, 3) + "ay";
        }
        if (STARTS_WITH_CH_QU_TH_CONSONANT_CLUSTER_Y.matcher(s).matches()) {
            return rotate(s, 2) + "ay";
        }
        return rotate(s, 1) + "ay";
    }

    private String rotate(String s, int i) {
        return s.substring(i) + s.substring(0, i);
    }
}