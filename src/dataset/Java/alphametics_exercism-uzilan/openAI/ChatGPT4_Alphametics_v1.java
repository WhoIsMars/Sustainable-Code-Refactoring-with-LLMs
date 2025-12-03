import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Alphametics {

    private final List<String> words;
    private final List<String> adds;
    private final String result;
    private final Map<Character, Integer> map = new LinkedHashMap<>();

    public Alphametics(String expression) throws UnsolvablePuzzleException {
        words = List.of(expression.split("\\+|=="))
                .stream()
                .map(String::trim)
                .toList();

        adds = words.subList(0, words.size() - 1);
        result = words.get(words.size() - 1);

        final List<Character> letters = words.stream()
                .flatMapToInt(String::chars)
                .mapToObj(c -> (char) c)
                .distinct()
                .toList();

        if (!exhaustiveSolve(letters, 0)) {
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

        char currentLetter = lettersToAssign.get(index);
        for (int digit = 9; digit >= 0; digit--) {
            if (assignLetterToDigit(currentLetter, digit)) {
                if (exhaustiveSolve(lettersToAssign, index + 1)) {
                    return true;
                }
                unassignLetterFromDigit(currentLetter);
            }
        }
        return false;
    }

    private boolean isPuzzleSolved() {
        long sum = 0;
        for (String add : adds) {
            long value = replaceWithNumbers(add);
            if (value == -1) return false;
            sum += value;
        }

        long resultSum = replaceWithNumbers(result);
        return resultSum != -1 && sum == resultSum && noWordBeginWithZero();
    }

    private boolean noWordBeginWithZero() {
        for (String word : words) {
            if (map.get(word.charAt(0)) == 0) {
                return false;
            }
        }
        return true;
    }

    private long replaceWithNumbers(String s) {
        long number = 0;
        for (char c : s.toCharArray()) {
            Integer digit = map.get(c);
            if (digit == null) return -1;
            number = number * 10 + digit;
        }
        return number;
    }

    private boolean assignLetterToDigit(char c, int digit) {
        if (map.containsKey(c) || map.containsValue(digit)) {
            return false;
        }
        map.put(c, digit);
        return true;
    }

    private void unassignLetterFromDigit(char c) {
        map.remove(c);
    }

    public static class UnsolvablePuzzleException extends Exception {
        public UnsolvablePuzzleException() {
            super("Puzzle cannot be solved");
        }
    }
}