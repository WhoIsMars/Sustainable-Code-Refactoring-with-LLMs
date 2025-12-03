import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Anagram {

    private final String string;
    private final Map<Integer, Long> map;

    public Anagram(String string) {
        this.string = string.toLowerCase();
        this.map = createCharFrequencyMap(this.string);
    }

    public List<String> match(List<String> strings) {
        return strings.stream()
                .filter(word -> {
                    String lowerWord = word.toLowerCase();
                    return !lowerWord.equals(string) && createCharFrequencyMap(lowerWord).equals(map);
                })
                .toList();
    }

    private Map<Integer, Long> createCharFrequencyMap(String word) {
        return word.chars()
                .boxed()
                .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));
    }
}