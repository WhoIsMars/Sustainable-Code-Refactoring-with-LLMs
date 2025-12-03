import java.util.HashSet;

public class PangramChecker {

    public boolean isPangram(String input) {
        if (input == null || input.length() < 26) {
            return false;
        }

        HashSet<Character> seenLetters = new HashSet<>();
        input = input.toLowerCase();

        for (char ch : input.toCharArray()) {
            if (ch >= 'a' && ch <= 'z') {
                seenLetters.add(ch);
                if (seenLetters.size() == 26) {
                    return true;
                }
            }
        }

        return false;
    }
}