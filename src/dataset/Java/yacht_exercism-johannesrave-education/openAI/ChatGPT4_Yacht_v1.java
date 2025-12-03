import java.util.HashMap;
import java.util.Map;

class Yacht {

    private final int[] dice;
    private final YachtCategory category;
    private final Map<Integer, Integer> frequencyMap;

    Yacht(int[] dice, YachtCategory yachtCategory) {
        this.dice = dice;
        this.category = yachtCategory;
        this.frequencyMap = calculateFrequency();
    }

    int score() {
        switch (category) {
            case ONES: return sumOfNum(1);
            case TWOS: return sumOfNum(2);
            case THREES: return sumOfNum(3);
            case FOURS: return sumOfNum(4);
            case FIVES: return sumOfNum(5);
            case SIXES: return sumOfNum(6);
            case FULL_HOUSE: return fullHouse();
            case FOUR_OF_A_KIND: return fourOfAKind();
            case LITTLE_STRAIGHT: return straight(new int[]{1, 2, 3, 4, 5});
            case BIG_STRAIGHT: return straight(new int[]{2, 3, 4, 5, 6});
            case CHOICE: return summed();
            case YACHT: return yacht();
            default: return 0;
        }
    }

    private int sumOfNum(int i) {
        return frequencyMap.getOrDefault(i, 0) * i;
    }

    private int fullHouse() {
        boolean hasThree = false, hasTwo = false;
        for (int count : frequencyMap.values()) {
            if (count == 3) hasThree = true;
            if (count == 2) hasTwo = true;
        }
        return (hasThree && hasTwo) ? summed() : 0;
    }

    private int fourOfAKind() {
        for (Map.Entry<Integer, Integer> entry : frequencyMap.entrySet()) {
            if (entry.getValue() >= 4) {
                return 4 * entry.getKey();
            }
        }
        return 0;
    }

    private int summed() {
        int sum = 0;
        for (Map.Entry<Integer, Integer> entry : frequencyMap.entrySet()) {
            sum += entry.getKey() * entry.getValue();
        }
        return sum;
    }

    private int straight(int[] straight) {
        int[] diceCopy = dice.clone();
        java.util.Arrays.sort(diceCopy);
        for (int i = 0; i < straight.length; i++) {
            if (diceCopy[i] != straight[i]) return 0;
        }
        return 30;
    }

    private int yacht() {
        return frequencyMap.containsValue(5) ? 50 : 0;
    }

    private Map<Integer, Integer> calculateFrequency() {
        Map<Integer, Integer> map = new HashMap<>();
        for (int die : dice) {
            map.put(die, map.getOrDefault(die, 0) + 1);
        }
        return map;
    }
}