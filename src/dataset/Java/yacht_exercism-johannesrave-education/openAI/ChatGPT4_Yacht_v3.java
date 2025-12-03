import java.util.Arrays;

class Yacht {

    private final int[] dice;
    private final YachtCategory category;

    Yacht(int[] dice, YachtCategory yachtCategory) {
        this.dice = dice;
        this.category = yachtCategory;
    }

    int score() {
        return switch (category) {
            case ONES -> sumOfNum(1);
            case TWOS -> sumOfNum(2);
            case THREES -> sumOfNum(3);
            case FOURS -> sumOfNum(4);
            case FIVES -> sumOfNum(5);
            case SIXES -> sumOfNum(6);
            case FULL_HOUSE -> fullHouse();
            case FOUR_OF_A_KIND -> fourOfAKind();
            case LITTLE_STRAIGHT -> straight(new int[]{1, 2, 3, 4, 5});
            case BIG_STRAIGHT -> straight(new int[]{2, 3, 4, 5, 6});
            case CHOICE -> summed();
            case YACHT -> yacht();
        };
    }

    private int sumOfNum(int i) {
        int sum = 0;
        for (int die : dice) {
            if (die == i) sum += i;
        }
        return sum;
    }

    private int fullHouse() {
        int[] counts = new int[7];
        for (int die : dice) counts[die]++;
        boolean hasThree = false, hasTwo = false;
        for (int count : counts) {
            if (count == 3) hasThree = true;
            if (count == 2) hasTwo = true;
        }
        return (hasThree && hasTwo) ? summed() : 0;
    }

    private int fourOfAKind() {
        int[] counts = new int[7];
        for (int die : dice) counts[die]++;
        for (int i = 1; i <= 6; i++) {
            if (counts[i] >= 4) return 4 * i;
        }
        return 0;
    }

    private int summed() {
        int sum = 0;
        for (int die : dice) sum += die;
        return sum;
    }

    private int straight(int[] target) {
        int[] sortedDice = Arrays.copyOf(dice, dice.length);
        Arrays.sort(sortedDice);
        return Arrays.equals(sortedDice, target) ? 30 : 0;
    }

    private int yacht() {
        int first = dice[0];
        for (int die : dice) {
            if (die != first) return 0;
        }
        return 50;
    }
}