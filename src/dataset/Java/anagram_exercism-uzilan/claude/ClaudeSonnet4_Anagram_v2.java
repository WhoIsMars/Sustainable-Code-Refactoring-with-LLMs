import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Anagram {

    private final String string;
    private final char[] sortedChars;

    public Anagram(String string) {
        this.string = string;
        this.sortedChars = getSortedChars(string);
    }

    public List<String> match(List<String> strings) {
        List<String> result = new ArrayList<>();
        for (String word : strings) {
            if (!word.equalsIgnoreCase(string) && Arrays.equals(sortedChars, getSortedChars(word))) {
                result.add(word);
            }
        }
        return result;
    }

    private char[] getSortedChars(String word) {
        char[] chars = word.toLowerCase().toCharArray();
        Arrays.sort(chars);
        return chars;
    }
}