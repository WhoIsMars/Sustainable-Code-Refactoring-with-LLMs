public class PangramChecker {
    private static final int ALPHABET_SIZE = 26;
    private static final int LETTER_A = 'a';

    public boolean isPangram(String input) {
        if (input == null || input.length() < ALPHABET_SIZE) {
            return false;
        }
        
        boolean[] lettersSeen = new boolean[ALPHABET_SIZE];
        int uniqueLettersCount = 0;
        
        for (int i = 0; i < input.length() && uniqueLettersCount < ALPHABET_SIZE; i++) {
            char c = input.charAt(i);
            if (c >= 'A' && c <= 'Z') {
                c = (char) (c + 32);
            }
            if (c >= 'a' && c <= 'z') {
                int index = c - LETTER_A;
                if (!lettersSeen[index]) {
                    lettersSeen[index] = true;
                    uniqueLettersCount++;
                }
            }
        }
        
        return uniqueLettersCount == ALPHABET_SIZE;
    }
}