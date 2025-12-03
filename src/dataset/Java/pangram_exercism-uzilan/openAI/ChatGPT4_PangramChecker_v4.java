import java.util.BitSet;

public class PangramChecker {

    public boolean isPangram(String input) {
        if (input == null || input.length() < 26) return false;
        BitSet alphabetSet = new BitSet(26);
        int uniqueLetters = 0;
        for (char c : input.toCharArray()) {
            if (c >= 'A' && c <= 'Z') c += 32; // Convert to lowercase
            if (c >= 'a' && c <= 'z') {
                int index = c - 'a';
                if (!alphabetSet.get(index)) {
                    alphabetSet.set(index);
                    uniqueLetters++;
                    if (uniqueLetters == 26) return true;
                }
            }
        }
        return false;
    }
}