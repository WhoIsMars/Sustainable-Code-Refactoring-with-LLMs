import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Anagram {

    private final String string;
    private final Map<Integer, Long> charCounts;
    private final int stringLength;
    private final int[] stringCodePoints;

    public Anagram(String string) {
        this.string = string;
        this.stringLength = string.length();
        this.stringCodePoints = string.toLowerCase().codePoints().toArray();
        this.charCounts = Arrays.stream(stringCodePoints)
                .boxed()
                .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));
    }

    public List<String> match(List<String> strings) {
        return strings.stream()
                .filter(word -> !word.equalsIgnoreCase(string) && word.length() == stringLength && isAnagram(word))
                .collect(Collectors.toList());
    }

    private boolean isAnagram(String word) {
        if (word.length() != stringLength) {
            return false;
        }

        int[] wordCodePoints = word.toLowerCase().codePoints().toArray();
        if (wordCodePoints.length != stringCodePoints.length) {
            return false;
        }

        Map<Integer, Long> wordCharCounts = Arrays.stream(wordCodePoints)
                .boxed()
                .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));

        return wordCharCounts.equals(charCounts);
    }

    private Map<Integer, Long> getWordMap(String word) {
        return word
                .toLowerCase()
                .codePoints()
                .boxed()
                .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));
    }
}