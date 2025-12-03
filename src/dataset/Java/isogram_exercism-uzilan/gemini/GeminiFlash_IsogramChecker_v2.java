import java.util.HashSet;
import java.util.Set;

class IsogramChecker {

    boolean isIsogram(String phrase) {
        phrase = phrase.toLowerCase();
        Set<Character> seen = new HashSet<>();
        for (int i = 0; i < phrase.length(); i++) {
            char c = phrase.charAt(i);
            if (Character.isLetter(c)) {
                if (seen.contains(c)) {
                    return false;
                }
                seen.add(c);
            }
        }
        return true;
    }
}