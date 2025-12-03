public class PangramChecker {

    public boolean isPangram(String input) {
        if (input == null || input.length() < 26) {
            return false;
        }

        boolean[] alphabetPresent = new boolean[26];
        int count = 0;

        for (int i = 0; i < input.length(); i++) {
            char c = Character.toLowerCase(input.charAt(i));
            if ('a' <= c && c <= 'z') {
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