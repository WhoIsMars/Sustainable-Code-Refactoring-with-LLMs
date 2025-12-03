import java.util.StringJoiner;

public class PigLatinTranslator {

    public String translate(String string) {
        String[] words = string.split(" ");
        StringJoiner result = new StringJoiner(" ");
        for (String word : words) {
            result.add(translateWord(word));
        }
        return result.toString();
    }

    private String translateWord(String s) {
        if (startsWithVowelOrSpecial(s)) {
            return s + "ay";
        }
        if (startsWithThrSchOrConsonantQu(s)) {
            return rotate(s, 3) + "ay";
        }
        if (startsWithChQuThOrConsonantClusterY(s)) {
            return rotate(s, 2) + "ay";
        }
        return rotate(s, 1) + "ay";
    }

    private boolean startsWithVowelOrSpecial(String s) {
        char first = s.charAt(0);
        return "aeiou".indexOf(first) >= 0 || s.startsWith("yt") || s.startsWith("xr");
    }

    private boolean startsWithThrSchOrConsonantQu(String s) {
        return s.startsWith("thr") || s.startsWith("sch") || s.matches("^[bcdfghjklmnpqrstvwxyz]qu.*");
    }

    private boolean startsWithChQuThOrConsonantClusterY(String s) {
        return s.startsWith("ch") || s.startsWith("qu") || s.startsWith("th") || s.matches("^[bcdfghjklmnpqrstvwxyz]{2,}y.*");
    }

    private String rotate(String s, int i) {
        return s.substring(i) + s.substring(0, i);
    }
}