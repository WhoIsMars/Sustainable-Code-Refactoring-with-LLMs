import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Anagram {

    private final String string;
    private final Map<Integer, Long> map;
    private final String lowerCaseString;

    public Anagram(String string) {
        this.string = string;
        this.lowerCaseString = string.toLowerCase();
        this.map = getWordMap(this.lowerCaseString);
    }

    public List<String> match(List<String> strings) {
        return strings.stream()
                .filter(word -> {
                    String lowerCaseWord = word.toLowerCase();
                    return !lowerCaseWord.equals(lowerCaseString) && getWordMap(lowerCaseWord).equals(map);
                })
                .collect(Collectors.toList());
    }

    private Map<Integer, Long> getWordMap(String word) {
        return word.codePoints()
                .boxed()
                .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));
    }
}