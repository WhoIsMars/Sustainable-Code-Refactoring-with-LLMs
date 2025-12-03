import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Anagram {
    private final String base;
    private final String sortedBase;

    public Anagram(String in) {
        this.base = in;
        this.sortedBase = sortString(in.toLowerCase());
    }

    private String sortString(String str) {
        char[] chars = str.toCharArray();
        Arrays.sort(chars);
        return new String(chars);
    }

    public List<String> match(List<String> candidates) {
        List<String> result = new ArrayList<>();
        String lowerBase = base.toLowerCase();

        for (String candidate : candidates) {
            String lowerCandidate = candidate.toLowerCase();
            if (!lowerBase.equals(lowerCandidate) && lowerCandidate.length() == base.length()) {
                if (sortedBase.equals(sortString(lowerCandidate))) {
                    result.add(candidate);
                }
            }
        }
        return result;
    }
}