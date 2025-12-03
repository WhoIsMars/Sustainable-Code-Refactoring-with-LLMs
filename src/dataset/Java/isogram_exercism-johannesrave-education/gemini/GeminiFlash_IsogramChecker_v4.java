import java.util.HashSet;

class IsogramChecker {

    boolean isIsogram(String phrase) {
        String cleanPhrase = phrase.replaceAll("\\W", "").toLowerCase();
        int phraseLength = cleanPhrase.length();

        if (phraseLength == 0) {
            return true;
        }

        HashSet<Character> letters = new HashSet<>(phraseLength);

        for (int i = 0; i < phraseLength; i++) {
            char letter = cleanPhrase.charAt(i);
            if (!letters.add(letter)) {
                return false;
            }
        }

        return true;
    }
}