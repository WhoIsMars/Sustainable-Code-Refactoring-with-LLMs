import java.util.Arrays;

class Yacht {

    private final int[] dice;
    private final YachtCategory category;

    Yacht(int[] dice, YachtCategory yachtCategory) {
        this.dice = dice;
        this.category = yachtCategory;
    }

    int score() {
        switch (category){
            case ONES: return sumOfNum(1);
            case TWOS: return sumOfNum(2);
            case THREES: return sumOfNum(3);
            case FOURS: return sumOfNum(4);
            case FIVES: return sumOfNum(5);
            case SIXES: return sumOfNum(6);
            case FULL_HOUSE: return fullHouse();
            case FOUR_OF_A_KIND: return fourOfAKind();
            case LITTLE_STRAIGHT: return straight(1);
            case BIG_STRAIGHT: return straight(2);
            case CHOICE: return summed();
            case YACHT: return yacht();
            default: return 0;
        }
    }

    private int sumOfNum(int i) {
        int sum = 0;
        for (int die : dice) {
            if (die == i) {
                sum += i;
            }
        }
        return sum;
    }

    private int fullHouse() {
        int[] counts = new int[7];
        for (int die : dice) {
            counts[die]++;
        }

        boolean hasThree = false;
        boolean hasTwo = false;
        for (int count : counts) {
            if (count == 3) {
                hasThree = true;
            } else if (count == 2) {
                hasTwo = true;
            }
        }

        if (hasThree && hasTwo) {
            return summed();
        }
        return 0;
    }

    private int fourOfAKind() {
        int[] counts = new int[7];
        for (int die : dice) {
            counts[die]++;
        }

        for (int i = 1; i <= 6; i++) {
            if (counts[i] >= 4) {
                return 4 * i;
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

    private int straight(int start) {
        int[] expected = new int[5];
        for (int i = 0; i < 5; i++) {
            expected[i] = start + i;
        }
        Arrays.sort(dice);
        if (Arrays.equals(dice, expected)) {
            return 30;
        }
        return 0;
    }

    private int yacht() {
        if (dice[0] == dice[1] && dice[0] == dice[2] && dice[0] == dice[3] && dice[0] == dice[4]) {
            return 50;
        }
        return 0;
    }

    private int occurs(int die){
        int count = 0;
        for (int d : dice) {
            if (d == die) {
                count++;
            }
        }
        return count;
    }
}