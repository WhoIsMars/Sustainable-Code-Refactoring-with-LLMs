import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Alphametics {

    private final List<String> words;
    private final List<String> adds;
    private final String result;
    private final Map<Character, Integer> map = new HashMap<>();
    private final Set<Integer> usedDigits = new HashSet<>();
    private final Set<Character> firstLetters = new HashSet<>();

    public Alphametics(String expression) throws UnsolvablePuzzleException {
        String[] parts = expression.split("\\+|==");
        words = new ArrayList<>();
        for (String part : parts) {
            words.add(part.trim());
        }

        adds = words.subList(0, words.size() - 1);
        result = words.get(words.size() - 1);

        Set<Character> letters = new HashSet<>();
        for (String word : words) {
            for (int i = 0; i < word.length(); i++) {
                letters.add(word.charAt(i));
                if (i == 0) {
                    firstLetters.add(word.charAt(0));
                }
            }
        }

        List<Character> lettersToAssign = new ArrayList<>(letters);

        if (!exhaustiveSolve(lettersToAssign, 0)) {
            throw new UnsolvablePuzzleException();
        }
    }

    public Map<Character, Integer> solve() {
        return map;
    }

    private boolean exhaustiveSolve(List<Character> lettersToAssign, int index) {
        if (index == lettersToAssign.size()) {
            return isPuzzleSolved();
        }

        char letter = lettersToAssign.get(index);
        for (int digit = 9; digit >= 0; digit--) {
            if (!usedDigits.contains(digit) && (!firstLetters.contains(letter) || digit != 0)) {
                map.put(letter, digit);
                usedDigits.add(digit);

                if (exhaustiveSolve(lettersToAssign, index + 1)) {
                    return true;
                }

                map.remove(letter);
                usedDigits.remove(digit);
            }
        }
        return false;
    }

    private boolean isPuzzleSolved() {
        long sum = 0;
        for (String add : adds) {
            sum += replaceWithNumbers(add);
        }

        final long resultSum = replaceWithNumbers(result);

        return sum == resultSum;
    }

    private long replaceWithNumbers(String s) {
        long num = 0;
        for (int i = 0; i < s.length(); i++) {
            num = num * 10 + map.get(s.charAt(i));
        }
        return num;
    }
}