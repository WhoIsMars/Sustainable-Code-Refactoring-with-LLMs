import java.util.HashSet;

public class Pangrams {
    public static boolean isPangram(String words) {
        if (words == null || words.length() < 26) return false;
        HashSet<Character> alphabetSet = new HashSet<>();
        for (char c : words.toLowerCase().toCharArray()) {
            if (c >= 'a' && c <= 'z') {
                alphabetSet.add(c);
                if (alphabetSet.size() == 26) return true;
            }
        }
        return false;
    }
}