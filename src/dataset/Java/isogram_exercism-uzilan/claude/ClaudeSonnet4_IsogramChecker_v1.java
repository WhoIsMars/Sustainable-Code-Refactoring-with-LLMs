import java.util.HashSet;
import java.util.Set;

class IsogramChecker {

    boolean isIsogram(String phrase) {
        Set<Character> seen = new HashSet<>();
        
        for (int i = 0; i < phrase.length(); i++) {
            char c = phrase.charAt(i);
            if (Character.isLetter(c)) {
                char lowerC = Character.toLowerCase(c);
                if (!seen.add(lowerC)) {
                    return false;
                }
            }
        }
        
        return true;
    }
}