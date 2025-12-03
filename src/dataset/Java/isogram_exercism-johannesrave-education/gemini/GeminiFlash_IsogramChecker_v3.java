import java.util.HashSet;

class IsogramChecker {

    boolean isIsogram(String phrase) {
        String cleanPhrase = phrase.replaceAll("[^a-zA-Z]","").toLowerCase();
        int len = cleanPhrase.length();

        if (len == 0) {
            return true;
        }

        HashSet<Character> seen = new HashSet<>(len);
        for (int i = 0; i < len; i++) {
            char c = cleanPhrase.charAt(i);
            if (!seen.add(c)) {
                return false;
            }
        }

        return true;
    }
}