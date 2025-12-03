public class Pangrams {
    public static boolean isPangram(String words) {
        words = words.toLowerCase();
        boolean[] alphabetPresent = new boolean[26];
        int count = 0;

        for (int i = 0; i < words.length(); i++) {
            char c = words.charAt(i);
            if (c >= 'a' && c <= 'z') {
                int index = c - 'a';
                if (!alphabetPresent[index]) {
                    alphabetPresent[index] = true;
                    count++;
                    if (count == 26) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}