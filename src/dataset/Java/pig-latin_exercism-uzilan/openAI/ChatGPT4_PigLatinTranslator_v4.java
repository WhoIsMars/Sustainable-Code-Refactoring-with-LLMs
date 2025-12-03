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
        if (startsWithVowelOrSpecial(s)) {
            return s + "ay";
        }
        int rotateIndex = getRotateIndex(s);
        return s.substring(rotateIndex) + s.substring(0, rotateIndex) + "ay";
    }

    private boolean startsWithVowelOrSpecial(String s) {
        char first = s.charAt(0);
        return "aeiou".indexOf(first) >= 0 || s.startsWith("yt") || s.startsWith("xr");
    }

    private int getRotateIndex(String s) {
        if (s.startsWith("thr") || s.startsWith("sch") || s.matches("^[bcdfghjklmnpqrstvwxyz]qu.*")) {
            return 3;
        }
        if (s.startsWith("ch") || s.startsWith("qu") || s.startsWith("th") || s.matches("^([bcdfghjklmnpqrstvwxyz]{2,}y).*")) {
            return 2;
        }
        return 1;
    }
}