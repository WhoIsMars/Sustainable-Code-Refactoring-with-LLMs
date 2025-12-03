import java.util.HashSet;
import java.util.Set;

class IsogramChecker {

    boolean isIsogram(String phrase) {
        String lowerCasePhrase = phrase.toLowerCase();
        Set<Character> seenCharacters = new HashSet<>();

        for (int i = 0; i < lowerCasePhrase.length(); i++) {
            char c = lowerCasePhrase.charAt(i);
            if (Character.isLetter(c)) {
                if (seenCharacters.contains(c)) {
                    return false;
                }
                seenCharacters.add(c);
            }
        }

        return true;
    }
}