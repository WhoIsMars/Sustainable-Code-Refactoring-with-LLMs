import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class Alphametics {

    private final List<String> words;
    private final List<String> adds;
    private final String result;
    private final Map<Character, Integer> map = new LinkedHashMap<>();
    private final boolean[] usedDigits = new boolean[10];
    private final List<Character> uniqueLetters;
    private final Set<Character> leadingLetters;

    public Alphametics(String expression) throws UnsolvablePuzzleException {
        String[] parts = expression.split("\\+|==");
        words = new ArrayList<>(parts.length);
        for (String part : parts) {
            words.add(part.trim());
        }

        adds = words.subList(0, words.size() - 1);
        result = words.get(words.size() - 1);

        Set<Character> letterSet = new HashSet<>();
        leadingLetters = new HashSet<>();
        
        for (String word : words) {
            if (!word.isEmpty()) {
                leadingLetters.add(word.charAt(0));
                for (int i = 0; i < word.length(); i++) {
                    letterSet.add(word.charAt(i));
                }
            }
        }

        uniqueLetters = new ArrayList<>(letterSet);

        if (!exhaustiveSolve(0)) {
            throw new UnsolvablePuzzleException();
        }
    }

    public Map<Character, Integer> solve() {
        return map;
    }

    private boolean exhaustiveSolve(int letterIndex) {
        if (letterIndex == uniqueLetters.size()) {
            return isPuzzleSolved();
        }

        char letter = uniqueLetters.get(letterIndex);
        int startDigit = leadingLetters.contains(letter) ? 1 : 0;
        
        for (int digit = 9; digit >= startDigit; digit--) {
            if (!usedDigits[digit]) {
                usedDigits[digit] = true;
                map.put(letter, digit);
                
                if (exhaustiveSolve(letterIndex + 1)) {
                    return true;
                }
                
                map.remove(letter);
                usedDigits[digit] = false;
            }
        }
        return false;
    }

    private boolean isPuzzleSolved() {
        long sum = 0;
        for (String add : adds) {
            sum += replaceWithNumbers(add);
        }
        return sum == replaceWithNumbers(result);
    }

    private boolean noWordBeginWithZero() {
        for (String word : words) {
            if (!word.isEmpty() && map.get(word.charAt(0)) == 0) {
                return false;
            }
        }
        return true;
    }

    private long replaceWithNumbers(String s) {
        long result = 0;
        for (int i = 0; i < s.length(); i++) {
            result = result * 10 + map.get(s.charAt(i));
        }
        return result;
    }

    private boolean assignLetterToDigit(char c, Long digit) {
        final int i = digit.intValue();
        if (map.containsKey(c) || map.containsValue(i)) {
            return false;
        }

        map.put(c, i);
        return true;
    }

    private void unassignLetterFromDigit(char c) {
        map.remove(c);
    }
}