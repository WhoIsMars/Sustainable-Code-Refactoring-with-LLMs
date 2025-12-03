import java.util.Arrays;
import java.util.stream.Collectors;

public class PigLatinTranslator {

    public String translate(String string) {
        return Arrays.stream(string.split(" "))
                .map(this::processWord)
                .collect(Collectors.joining(" "));
    }

    private String processWord(String s) {
        if (startsWithVowelOrSpecial(s)) {
            return s + "ay";
        }
        int rotationIndex = getRotationIndex(s);
        return s.substring(rotationIndex) + s.substring(0, rotationIndex) + "ay";
    }

    private boolean startsWithVowelOrSpecial(String s) {
        char first = s.charAt(0);
        return "aeiou".indexOf(first) >= 0 || s.startsWith("yt") || s.startsWith("xr");
    }

    private int getRotationIndex(String s) {
        if (s.startsWith("thr") || s.startsWith("sch") || s.matches("^[bcdfghjklmnpqrstvwxyz]qu.*")) {
            return 3;
        }
        if (s.startsWith("ch") || s.startsWith("qu") || s.startsWith("th") || s.matches("^([bcdfghjklmnpqrstvwxyz]{2,}y).*")) {
            return 2;
        }
        return 1;
    }
}