import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Alphametics {

    private final List<String> words;
    private final List<String> adds;
    private final String result;
    private final Map<Character, Integer> map = new HashMap<>();
    private final boolean[] usedDigits = new boolean[10];
    private final char[] letters;

    public Alphametics(String expression) throws UnsolvablePuzzleException {
        String[] parts = expression.split("\\+|==");
        words = new ArrayList<>(parts.length);
        for (String part : parts) {
            words.add(part.trim());
        }

        adds = words.subList(0, words.size() - 1);
        result = words.get(words.size() - 1);

        boolean[] letterSeen = new boolean[256];
        List<Character> letterList = new ArrayList<>();
        
        for (String word : words) {
            for (int i = 0; i < word.length(); i++) {
                char c = word.charAt(i);
                if (!letterSeen[c]) {
                    letterSeen[c] = true;
                    letterList.add(c);
                }
            }
        }
        
        letters = new char[letterList.size()];
        for (int i = 0; i < letterList.size(); i++) {
            letters[i] = letterList.get(i);
        }

        if (!exhaustiveSolve(0)) {
            throw new UnsolvablePuzzleException();
        }
    }

    public Map<Character, Integer> solve() {
        return map;
    }

    private boolean exhaustiveSolve(int letterIndex) {
        if (letterIndex == letters.length) {
            return isPuzzleSolved();
        }

        char letter = letters[letterIndex];
        for (int digit = 9; digit >= 0; digit--) {
            if (!usedDigits[digit]) {
                map.put(letter, digit);
                usedDigits[digit] = true;
                
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
        if (!noWordBeginWithZero()) {
            return false;
        }

        long sum = 0;
        for (String add : adds) {
            sum += replaceWithNumbers(add);
        }

        return sum == replaceWithNumbers(result);
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