import java.util.BitSet;

class IsogramChecker {

    boolean isIsogram(String phrase) {
        String cleanPhrase = phrase.replaceAll("\\W", "").toLowerCase();
        BitSet seen = new BitSet(26);

        for (char letter : cleanPhrase.toCharArray()) {
            int index = letter - 'a';
            if (seen.get(index)) {
                return false;
            }
            seen.set(index);
        }

        return true;
    }

}