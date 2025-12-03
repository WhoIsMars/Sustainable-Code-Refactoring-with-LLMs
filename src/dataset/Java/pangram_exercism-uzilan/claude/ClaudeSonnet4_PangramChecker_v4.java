public class PangramChecker {

    public boolean isPangram(String input) {
        if (input == null || input.length() < 26) {
            return false;
        }
        
        boolean[] lettersSeen = new boolean[26];
        int uniqueLetters = 0;
        
        for (int i = 0; i < input.length() && uniqueLetters < 26; i++) {
            char c = input.charAt(i);
            if (c >= 'A' && c <= 'Z') {
                int index = c - 'A';
                if (!lettersSeen[index]) {
                    lettersSeen[index] = true;
                    uniqueLetters++;
                }
            } else if (c >= 'a' && c <= 'z') {
                int index = c - 'a';
                if (!lettersSeen[index]) {
                    lettersSeen[index] = true;
                    uniqueLetters++;
                }
            }
        }
        
        return uniqueLetters == 26;
    }
}