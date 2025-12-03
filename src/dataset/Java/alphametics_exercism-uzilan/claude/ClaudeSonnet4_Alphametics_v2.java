import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Alphametics {

    private final List<String> adds;
    private final String result;
    private final Map<Character, Integer> map = new HashMap<>();
    private final boolean[] usedDigits = new boolean[10];
    private final char[] letters;
    private final int letterCount;

    public Alphametics(String expression) throws UnsolvablePuzzleException {
        String[] parts = expression.split("\\+|==");
        adds = new ArrayList<>(parts.length - 1);
        for (int i = 0; i < parts.length - 1; i++) {
            adds.add(parts[i].trim());
        }
        result = parts[parts.length - 1].trim();

        // Extract unique letters more efficiently
        boolean[] letterExists = new boolean[256];
        List<Character> letterList = new ArrayList<>();
        
        for (String word : parts) {
            String trimmed = word.trim();
            for (int i = 0; i < trimmed.length(); i++) {
                char c = trimmed.charAt(i);
                if (!letterExists[c]) {
                    letterExists[c] = true;
                    letterList.add(c);
                }
            }
        }
        
        letters = new char[letterList.size()];
        for (int i = 0; i < letterList.size(); i++) {
            letters[i] = letterList.get(i);
        }
        letterCount = letters.length;

        if (!exhaustiveSolve(0)) {
            throw new UnsolvablePuzzleException();
        }
    }

    public Map<Character, Integer> solve() {
        return map;
    }

    private boolean exhaustiveSolve(int letterIndex) {
        if (letterIndex == letterCount) {
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
        // Check leading zeros first (early termination)
        for (String word : adds) {
            if (map.get(word.charAt(0)) == 0) {
                return false;
            }
        }
        if (map.get(result.charAt(0)) == 0) {
            return false;
        }

        long sum = 0;
        for (String add : adds) {
            sum += replaceWithNumbers(add);
        }

        return sum == replaceWithNumbers(result);
    }

    private long replaceWithNumbers(String s) {
        long value = 0;
        for (int i = 0; i < s.length(); i++) {
            value = value * 10 + map.get(s.charAt(i));
        }
        return value;
    }
}