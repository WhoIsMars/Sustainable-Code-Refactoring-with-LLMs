public class PigLatinTranslator {

    public String translate(String string) {
        String[] words = string.split(" ");
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < words.length; i++) {
            result.append(translateWord(words[i])).append("ay");
            if (i < words.length - 1) {
                result.append(" ");
            }
        }
        return result.toString();
    }

    private String translateWord(String s) {
        int len = s.length();
        if (len == 0) {
            return s;
        }

        char firstChar = s.charAt(0);
        if (isVowel(firstChar) || (firstChar == 'y' && len > 1) || (firstChar == 'x' && len > 1 && s.charAt(1) == 'r')) {
            return s;
        }

        if (len >= 3 && s.startsWith("thr")) {
            return s.substring(3) + s.substring(0, 3);
        }
        if (len >= 3 && s.startsWith("sch")) {
            return s.substring(3) + s.substring(0, 3);
        }
        if (len >= 2 && s.startsWith("qu")) {
            return s.substring(2) + s.substring(0, 2);
        }

        if (len >= 3 && isConsonant(firstChar) && s.charAt(1) == 'q' && s.charAt(2) == 'u') {
            return s.substring(3) + s.substring(0, 3);
        }

        if (len >= 2 && s.startsWith("ch")) {
            return s.substring(2) + s.substring(0, 2);
        }
        if (len >= 2 && s.startsWith("th")) {
            return s.substring(2) + s.substring(0, 2);
        }

        if (len >= 3) {
            int consonantCount = 0;
            int i = 0;
            while (i < len && isConsonant(s.charAt(i))) {
                consonantCount++;
                i++;
            }
            if (consonantCount >= 2 && i < len && s.charAt(i) == 'y') {
                return s.substring(2) + s.substring(0, 2);
            }
        }

        return s.substring(1) + s.substring(0, 1);
    }

    private boolean isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

    private boolean isConsonant(char c) {
        return !isVowel(c);
    }
}