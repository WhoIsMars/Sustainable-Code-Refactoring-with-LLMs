import java.util.BitSet;

class IsogramChecker {

    boolean isIsogram(String phrase) {
        BitSet seen = new BitSet(26);
        
        for (int i = 0; i < phrase.length(); i++) {
            char c = phrase.charAt(i);
            if (Character.isLetter(c)) {
                int index = Character.toLowerCase(c) - 'a';
                if (seen.get(index)) {
                    return false;
                }
                seen.set(index);
            }
        }
        
        return true;
    }
}