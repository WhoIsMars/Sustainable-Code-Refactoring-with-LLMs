import java.util.Arrays;
import java.util.Map;
import java.util.Optional;
import java.util.function.Predicate;
import java.util.stream.Collectors;

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
        for (int die : dice) {
            if (die != first) {
                return 0;
            }
        }
        return 50;
    }

    private int numbersScore(final int[] dice, final int number) {
        int sum = 0;
        for (int die : dice) {
            if (die == number) {
                sum += number;
            }
        }
        return sum;
    }

    private int fullHouseScore(final int[] dice) {
        final Map<Integer, Long> grouped = groupResults(dice);
        boolean hasThree = false;
        boolean hasTwo = false;
        for (long count : grouped.values()) {
            if (count == 3) {
                hasThree = true;
            } else if (count == 2) {
                hasTwo = true;
            }
        }

        if (hasThree && hasTwo) {
            return Arrays.stream(dice).sum();
        }
        return 0;
    }

    private int fourOfAKindScore(final int[] dice) {
        final Map<Integer, Long> grouped = groupResults(dice);
        for (Map.Entry<Integer, Long> entry : grouped.entrySet()) {
            if (entry.getValue() >= 4) {
                return entry.getKey() * 4;
            }
        }
        return 0;
    }

    private int straightScore(final int[] dice, final int from, final int to) {
        boolean[] present = new boolean[to - from + 1];
        for (int die : dice) {
            if (die >= from && die <= to) {
                present[die - from] = true;
            } else {
                return 0;
            }
        }
        for (boolean p : present) {
            if (!p) {
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

    private Map<Integer, Long> groupResults(final int[] dice) {
        return Arrays.stream(dice)
                .boxed()
                .collect(Collectors.groupingBy(java.util.function.Function.identity(), Collectors.counting()));
    }

}