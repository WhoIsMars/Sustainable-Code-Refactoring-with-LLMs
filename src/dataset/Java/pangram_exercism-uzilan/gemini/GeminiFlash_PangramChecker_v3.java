public class PangramChecker {

    public boolean isPangram(String input) {
        if (input == null || input.length() < 26) {
            return false;
        }

        boolean[] present = new boolean[26];
        int count = 0;

        String lowercaseInput = input.toLowerCase();

        for (int i = 0; i < lowercaseInput.length(); i++) {
            char c = lowercaseInput.charAt(i);
            if ('a' <= c && c <= 'z') {
                int index = c - 'a';
                if (!present[index]) {
                    present[index] = true;
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