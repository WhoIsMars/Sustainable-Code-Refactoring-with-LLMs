import java.util.HashSet;

class IsogramChecker {

    boolean isIsogram(String phrase) {
        HashSet<Character> seen = new HashSet<>();
        
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