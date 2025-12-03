import java.util.List;
import java.util.Map;
import java.util.function.Function;
import java.util.stream.Collectors;

public class Anagram {

    private final String string;
    private final Map<Character, Long> map;

    public Anagram(String string) {
        this.string = string.toLowerCase();
        this.map = getWordMap(this.string);
    }

    public List<String> match(List<String> strings) {
        return strings.stream()
                .filter(word -> {
                    String lowerWord = word.toLowerCase();
                    return !lowerWord.equals(string) && getWordMap(lowerWord).equals(map);
                })
                .toList();
    }

    private Map<Character, Long> getWordMap(String word) {
        return word.chars()
                .mapToObj(c -> (char) c)
                .collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));
    }
}