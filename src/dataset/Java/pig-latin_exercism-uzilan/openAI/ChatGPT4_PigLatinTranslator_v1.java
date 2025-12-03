import java.util.Arrays;

public class PigLatinTranslator {

    public String translate(String string) {
        StringBuilder result = new StringBuilder();
        for (String word : string.split(" ")) {
            result.append(translateWord(word)).append(" ");
        }
        return result.toString().trim();
    }

    private String translateWord(String s) {
        if (s.isEmpty()) return s;
        char firstChar = s.charAt(0);
        if (isVowelStart(s, firstChar)) {
            return s + "ay";
        }
        if (s.startsWith("thr") || s.startsWith("sch") || s.startsWith("qu")) {
            return rotate(s, 3) + "ay";
        }
        if (s.startsWith("ch") || s.startsWith("th") || hasConsonantCluster(s)) {
            return rotate(s, 2) + "ay";
        }
        return rotate(s, 1) + "ay";
    }

    private boolean isVowelStart(String s, char firstChar) {
        return "aeiou".indexOf(firstChar) != -1 || s.startsWith("yt") || s.startsWith("xr");
    }

    private boolean hasConsonantCluster(String s) {
        return s.length() > 1 && isConsonant(s.charAt(0)) && s.charAt(1) == 'y';
    }

    private boolean isConsonant(char c) {
        return "bcdfghjklmnpqrstvwxyz".indexOf(c) != -1;
    }

    private String rotate(String s, int i) {
        return s.substring(i) + s.substring(0, i);
    }
}