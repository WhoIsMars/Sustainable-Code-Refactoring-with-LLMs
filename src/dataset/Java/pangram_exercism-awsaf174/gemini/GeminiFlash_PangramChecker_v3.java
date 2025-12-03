public class PangramChecker {

    public boolean isPangram(String input) {
        if (input == null || input.length() < 26) {
            return false;
        }

        boolean[] alphabetPresent = new boolean[26];
        input = input.toLowerCase();

        for (int i = 0; i < input.length(); i++) {
            char ch = input.charAt(i);
            if ('a' <= ch && ch <= 'z') {
                alphabetPresent[ch - 'a'] = true;
            }
        }

        for (boolean present : alphabetPresent) {
            if (!present) {
                return false;
            }
        }

        return true;
    }
}