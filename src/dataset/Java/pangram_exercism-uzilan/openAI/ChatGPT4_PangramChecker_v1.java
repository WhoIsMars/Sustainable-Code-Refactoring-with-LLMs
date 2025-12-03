import java.util.HashSet;
import java.util.Set;

public class PangramChecker {

    public boolean isPangram(String input) {
        if (input == null || input.length() < 26) return false;
        Set<Character> seen = new HashSet<>();
        for (char c : input.toLowerCase().toCharArray()) {
            if (c >= 'a' && c <= 'z') {
                seen.add(c);
                if (seen.size() == 26) return true;
            }
        }
        return false;
    }
}