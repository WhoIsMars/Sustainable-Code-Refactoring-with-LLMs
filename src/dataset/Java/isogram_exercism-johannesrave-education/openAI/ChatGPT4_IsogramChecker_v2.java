import java.util.HashSet;

class IsogramChecker {

    boolean isIsogram(String phrase) {
        String cleanPhrase = phrase.replaceAll("\\W", "").toLowerCase();
        HashSet<Character> seen = new HashSet<>();
        
        for (char letter : cleanPhrase.toCharArray()) {
            if (!seen.add(letter)) {
                return false;
            }
        }
        
        return true;
    }

}