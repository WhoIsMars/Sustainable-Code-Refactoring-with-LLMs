import java.util.HashSet;
import java.util.Set;

class IsogramChecker {

    boolean isIsogram(String phrase) {
        Set<Character> seen = new HashSet<>();
        for (char c : phrase.toLowerCase().toCharArray()) {
            if (Character.isLetter(c)) {
                if (!seen.add(c)) {
                    return false;
                }
            }
        }
        return true;
    }
}