import java.util.HashSet;

class IsogramChecker {

    boolean isIsogram(String phrase) {
        if (phrase == null || phrase.isEmpty()) return true;

        HashSet<Character> seen = new HashSet<>();
        for (char letter : phrase.toLowerCase().toCharArray()) {
            if (Character.isLetter(letter)) {
                if (!seen.add(letter)) {
                    return false;
                }
            }
        }
        return true;
    }

}