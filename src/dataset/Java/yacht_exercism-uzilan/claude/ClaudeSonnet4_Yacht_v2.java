import java.util.Arrays;

class Yacht {

    private int score;

    Yacht(int[] dice, YachtCategory yachtCategory) {
        score = calculateScore(dice, yachtCategory);
    }

    int score() {
        return score;
    }

    private int calculateScore(int[] dice, YachtCategory yachtCategory) {
        switch (yachtCategory) {
            case YACHT:
                return yachtScore(dice);
            case ONES:
                return numbersScore(dice, 1);
            case TWOS:
                return numbersScore(dice, 2);
            case THREES:
                return numbersScore(dice, 3);
            case FOURS:
                return numbersScore(dice, 4);
            case FIVES:
                return numbersScore(dice, 5);
            case SIXES:
                return numbersScore(dice, 6);
            case FULL_HOUSE:
                return fullHouseScore(dice);
            case FOUR_OF_A_KIND:
                return fourOfAKindScore(dice);
            case LITTLE_STRAIGHT:
                return straightScore(dice, 1, 5);
            case BIG_STRAIGHT:
                return straightScore(dice, 2, 6);
            case CHOICE:
                return choiceScore(dice);
            default:
                return 0;
        }
    }

    private int yachtScore(final int[] dice) {
        int first = dice[0];
        for (int i = 1; i < dice.length; i++) {
            if (dice[i] != first) {
                return 0;
            }
        }
        return 50;
    }

    private int numbersScore(final int[] dice, final int number) {
        int count = 0;
        for (int die : dice) {
            if (die == number) {
                count++;
            }
        }
        return count * number;
    }

    private int fullHouseScore(final int[] dice) {
        int[] counts = new int[7];
        int sum = 0;
        for (int die : dice) {
            counts[die]++;
            sum += die;
        }
        
        boolean hasThree = false;
        boolean hasTwo = false;
        for (int i = 1; i <= 6; i++) {
            if (counts[i] == 3) {
                hasThree = true;
            } else if (counts[i] == 2) {
                hasTwo = true;
            }
        }
        
        return (hasThree && hasTwo) ? sum : 0;
    }

    private int fourOfAKindScore(final int[] dice) {
        int[] counts = new int[7];
        for (int die : dice) {
            counts[die]++;
        }
        
        for (int i = 1; i <= 6; i++) {
            if (counts[i] >= 4) {
                return i * 4;
            }
        }
        return 0;
    }

    private int straightScore(final int[] dice, final int from, final int to) {
        boolean[] present = new boolean[7];
        for (int die : dice) {
            present[die] = true;
        }
        
        for (int i = from; i <= to; i++) {
            if (!present[i]) {
                return 0;
            }
        }
        return 30;
    }

    private int choiceScore(final int[] dice) {
        int sum = 0;
        for (int die : dice) {
            sum += die;
        }
        return sum;
    }
}