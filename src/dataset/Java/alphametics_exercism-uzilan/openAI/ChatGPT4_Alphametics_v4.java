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

        Set<Character> letters = new LinkedHashSet<>();
        for (String word : words) {
            for (char c : word.toCharArray()) {
                letters.add(c);
            }
        }

        if (!exhaustiveSolve(new ArrayList<>(letters))) {
            throw new UnsolvablePuzzleException();
        }
    }

    public Map<Character, Integer> solve() {
        return map;
    }

    private boolean exhaustiveSolve(List<Character> lettersToAssign) {
        if (lettersToAssign.isEmpty()) {
            return isPuzzleSolved();
        }

        char currentLetter = lettersToAssign.get(0);
        for (int digit = 9; digit >= 0; digit--) {
            if (!usedDigits.contains(digit)) {
                map.put(currentLetter, digit);
                usedDigits.add(digit);

                if (exhaustiveSolve(lettersToAssign.subList(1, lettersToAssign.size()))) {
                    return true;
                }

                map.remove(currentLetter);
                usedDigits.remove(digit);
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
        return resultSum != -1 && sum == resultSum && noWordBeginsWithZero();
    }

    private boolean noWordBeginsWithZero() {
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
}