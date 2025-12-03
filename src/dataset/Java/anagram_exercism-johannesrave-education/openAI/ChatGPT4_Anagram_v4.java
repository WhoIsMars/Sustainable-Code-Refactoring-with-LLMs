import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Anagram {
    private final String base;
    private final String sortedBase;

    public Anagram(String in) {
        this.base = in.toLowerCase();
        this.sortedBase = sortString(this.base);
    }

    public List<String> match(List<String> candidates) {
        return candidates.stream()
                .filter(candidate -> {
                    String lowerCandidate = candidate.toLowerCase();
                    return !base.equals(lowerCandidate) && sortedBase.equals(sortString(lowerCandidate));
                })
                .collect(Collectors.toList());
    }

    private String sortString(String input) {
        char[] chars = input.toCharArray();
        Arrays.sort(chars);
        return new String(chars);
    }
}