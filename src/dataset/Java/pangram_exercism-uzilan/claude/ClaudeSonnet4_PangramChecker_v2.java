public class PangramChecker {

    public boolean isPangram(String input) {
        boolean[] letters = new boolean[26];
        int count = 0;
        
        for (int i = 0; i < input.length() && count < 26; i++) {
            char c = input.charAt(i);
            if (c >= 'a' && c <= 'z') {
                int index = c - 'a';
                if (!letters[index]) {
                    letters[index] = true;
                    count++;
                }
            } else if (c >= 'A' && c <= 'Z') {
                int index = c - 'A';
                if (!letters[index]) {
                    letters[index] = true;
                    count++;
                }
            }
        }
        
        return count == 26;
    }
}