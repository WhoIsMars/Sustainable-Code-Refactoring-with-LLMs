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
            case LITTLE_STRAIGHT: return straight(1, 5);
            case BIG_STRAIGHT: return straight(2, 6);
            case CHOICE: return summed();
            case YACHT: return yacht();
            default: return 0;
        }
    }

    private int sumOfNum(int num) {
        return frequencyMap.getOrDefault(num, 0) * num;
    }

    private int fullHouse() {
        boolean hasThree = false, hasTwo = false;
        int sum = 0;
        for (Map.Entry<Integer, Integer> entry : frequencyMap.entrySet()) {
            int count = entry.getValue();
            if (count == 3) hasThree = true;
            if (count == 2) hasTwo = true;
            sum += entry.getKey() * count;
        }
        return (hasThree && hasTwo) ? sum : 0;
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
        for (int die : dice) {
            sum += die;
        }
        return sum;
    }

    private int straight(int start, int end) {
        for (int i = start; i <= end; i++) {
            if (!frequencyMap.containsKey(i)) {
                return 0;
            }
        }
        return 30;
    }

    private int yacht() {
        return frequencyMap.size() == 1 && frequencyMap.containsValue(5) ? 50 : 0;
    }

    private Map<Integer, Integer> calculateFrequency() {
        Map<Integer, Integer> map = new HashMap<>();
        for (int die : dice) {
            map.put(die, map.getOrDefault(die, 0) + 1);
        }
        return map;
    }
}