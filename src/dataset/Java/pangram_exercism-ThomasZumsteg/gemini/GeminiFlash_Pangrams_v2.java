public class Pangrams {
    public static boolean isPangram(String words) {
        /* isPangram checks if all letters of the alphabet are present */
        if (words == null || words.length() < 26) {
            return false;
        }

        boolean[] alphabetPresent = new boolean[26];
        words = words.toLowerCase();

        for (int i = 0; i < words.length(); i++) {
            char c = words.charAt(i);
            if (c >= 'a' && c <= 'z') {
                alphabetPresent[c - 'a'] = true;
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