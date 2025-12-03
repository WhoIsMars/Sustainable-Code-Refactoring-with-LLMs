import java.util.Arrays;
import java.util.stream.Collectors;

public class PigLatinTranslator {

    public String translate(String string) {
        return Arrays.stream(string.split(" "))
                .map(this::translateWord)
                .collect(Collectors.joining(" "));
    }

    private String translateWord(String s) {
        int len = s.length();
        if (len == 0) {
            return s;
        }

        char firstChar = s.charAt(0);
        if (isVowel(firstChar) || (firstChar == 'y' && len > 1) || (firstChar == 'x' && len > 1 && s.charAt(1) == 'r')) {
            return s + "ay";
        }

        if (len >= 3 && (s.startsWith("thr") || s.startsWith("sch"))) {
            return s.substring(3) + s.substring(0, 3) + "ay";
        }

        if (len >= 2 && (s.startsWith("ch") || s.startsWith("qu") || s.startsWith("th"))) {
            return s.substring(2) + s.substring(0, 2) + "ay";
        }

        if (len >= 2 && !isVowel(firstChar) && !isVowel(s.charAt(1)) && s.charAt(1) != 'y') {
            int consonantClusterLength = 0;
            for (int i = 0; i < len; i++) {
                if (!isVowel(s.charAt(i))) {
                    consonantClusterLength++;
                    if (i > 1 && s.charAt(i) == 'y') {
                        break;
                    }
                } else {
                    break;
                }
            }
            if (consonantClusterLength > 1 && s.charAt(consonantClusterLength -1) == 'y') {
                return s.substring(2) + s.substring(0, 2) + "ay";
            }
            if (consonantClusterLength > 0) {
                return s.substring(consonantClusterLength) + s.substring(0, consonantClusterLength) + "ay";
            }
        }

        int quIndex = s.indexOf("qu");
        if (quIndex == 0) {
            return s.substring(2) + s.substring(0, 2) + "ay";
        }

        return s.substring(1) + s.substring(0, 1) + "ay";
    }

    private boolean isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
}