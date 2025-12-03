import java.util.Arrays;
import java.util.stream.Collectors;

public class PigLatinTranslator {

    public String translate(String string) {
        return Arrays.stream(string.split(" "))
                .map(this::translateWord)
                .collect(Collectors.joining(" "));
    }

    private String translateWord(String s) {
        int firstVowelIndex = findFirstVowelIndex(s);
        if (firstVowelIndex == 0) {
            return s + "ay";
        } else if (s.startsWith("xr") || s.startsWith("yt")) {
            return s + "ay";
        } else if (s.startsWith("thr") || s.startsWith("sch")) {
            return rotate(s, 3) + "ay";
        } else if (s.startsWith("ch") || s.startsWith("qu") || s.startsWith("th")) {
            return rotate(s, 2) + "ay";
        } else if (firstVowelIndex > 0) {
            if (s.substring(firstVowelIndex - 1, firstVowelIndex).matches("[bcdfghjklmnpqrstvwxyz]") && s.substring(firstVowelIndex).startsWith("y")) {
                return rotate(s, 2) + "ay";
            }
            return rotate(s, 1) + "ay";
        } else {
            return s + "ay";
        }
    }

    private int findFirstVowelIndex(String s) {
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (isVowel(c)) {
                return i;
            }
        }
        return -1;
    }

    private boolean isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

    private String rotate(String s, int i) {
        return s.substring(i) + s.substring(0, i);
    }
}