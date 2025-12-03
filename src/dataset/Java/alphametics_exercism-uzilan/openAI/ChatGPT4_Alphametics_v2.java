import java.util.*;

public class Alphametics {

    private final List<String> words;
    private final List<String> adds;
    private final String result;
    private final Map<Character, Integer> map = new LinkedHashMap<>();
    private final Set<Integer> usedDigits = new HashSet<>();

    public Alphametics(String expression) throws UnsolvablePuzzleException {
        words = Arrays.stream(expression.split("\\+|=="))
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
        for (int digit = 0; digit <= 9; digit++) {
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
        long sum = adds.stream()
                .mapToLong(this::replaceWithNumbers)
                .sum();

        return sum == replaceWithNumbers(result) && noWordBeginWithZero();
    }

    private boolean noWordBeginWithZero() {
        return words.stream().noneMatch(w -> map.get(w.charAt(0)) == 0);
    }

    private long replaceWithNumbers(String s) {
        long number = 0;
        for (char c : s.toCharArray()) {
            number = number * 10 + map.get(c);
        }
        return number;
    }

    private boolean assignLetterToDigit(char c, int digit) {
        if (map.containsKey(c) || usedDigits.contains(digit)) {
            return false;
        }

        map.put(c, digit);
        usedDigits.add(digit);
        return true;
    }

    private void unassignLetterFromDigit(char c) {
        usedDigits.remove(map.remove(c));
    }

    public static class UnsolvablePuzzleException extends Exception {
        public UnsolvablePuzzleException() {
            super("Puzzle cannot be solved");
        }
    }
}