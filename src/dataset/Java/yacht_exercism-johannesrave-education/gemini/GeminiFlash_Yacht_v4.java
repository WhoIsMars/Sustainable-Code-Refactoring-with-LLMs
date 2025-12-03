import java.util.Arrays;

class Yacht {

    private final int[] dice;
    private final YachtCategory category;

    Yacht(int[] dice, YachtCategory yachtCategory) {
        this.dice = dice;
        this.category = yachtCategory;
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
            case LITTLE_STRAIGHT:
            case BIG_STRAIGHT: return straight();
            case CHOICE: return summed();
            case YACHT: return yacht();
            default: return 0;
        }
    }

    private int sumOfNum(int die) {
        int count = 0;
        for (int d : dice) {
            if (d == die) {
                count++;
            }
        }
        return count * die;
    }

    private int fullHouse() {
        int[] counts = new int[7]; // Indices 1-6 represent dice values
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
            if (counts[die] >= 4) {
                return 4 * die;
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

    private int straight() {
        boolean littleStraight = category == YachtCategory.LITTLE_STRAIGHT;
        int[] expected = littleStraight ? new int[]{1, 2, 3, 4, 5} : new int[]{2, 3, 4, 5, 6};

        int[] sortedDice = Arrays.copyOf(dice, dice.length);
        Arrays.sort(sortedDice);

        return Arrays.equals(sortedDice, expected) ? 30 : 0;
    }

    private int yacht() {
        int firstDie = dice[0];
        for (int die : dice) {
            if (die != firstDie) {
                return 0;
            }
        }
        return 50;
    }
}