import java.util.HashSet;

public class PangramChecker {

    public boolean isPangram(String input) {
        if (input == null || input.length() < 26) {
            return false;
        }

        HashSet<Character> uniqueChars = new HashSet<>();
        input = input.toLowerCase();

        for (char ch : input.toCharArray()) {
            if (ch >= 'a' && ch <= 'z') {
                uniqueChars.add(ch);
                if (uniqueChars.size() == 26) {
                    return true;
                }
            }
        }

        return false;
    }
}