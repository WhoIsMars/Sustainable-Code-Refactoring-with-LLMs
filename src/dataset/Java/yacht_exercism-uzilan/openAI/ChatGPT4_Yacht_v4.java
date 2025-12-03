import java.util.Map;
import java.util.Optional;
import java.util.function.Predicate;

import static java.util.Arrays.stream;
import static java.util.function.Function.identity;
import static java.util.stream.Collectors.*;
import static java.util.stream.IntStream.rangeClosed;

class Yacht {

    private final int score;

    Yacht(int[] dice, YachtCategory yachtCategory) {
        this.score = calculateScore(dice, yachtCategory);
    }

    int score() {
        return score;
    }

    private int calculateScore(int[] dice, YachtCategory yachtCategory) {
        return switch (yachtCategory) {
            case YACHT -> yachtScore(dice);
            case ONES, TWOS, THREES, FOURS, FIVES, SIXES -> numbersScore(dice, yachtCategory.ordinal() + 1);
            case FULL_HOUSE -> fullHouseScore(dice);
            case FOUR_OF_A_KIND -> fourOfAKindScore(dice);
            case LITTLE_STRAIGHT -> straightScore(dice, 1, 5);
            case BIG_STRAIGHT -> straightScore(dice, 2, 6);
            case CHOICE -> choiceScore(dice);
        };
    }

    private int yachtScore(final int[] dice) {
        return stream(dice).allMatch(d -> d == dice[0]) ? 50 : 0;
    }

    private int numbersScore(final int[] dice, final int number) {
        return stream(dice).filter(d -> d == number).sum();
    }

    private int fullHouseScore(final int[] dice) {
        var grouped = groupResults(dice);
        return grouped.size() == 2 && grouped.containsValue(3L) && grouped.containsValue(2L)
                ? stream(dice).sum()
                : 0;
    }

    private int fourOfAKindScore(final int[] dice) {
        return groupResults(dice).entrySet().stream()
                .filter(entry -> entry.getValue() >= 4)
                .mapToInt(entry -> entry.getKey() * 4)
                .findFirst()
                .orElse(0);
    }

    private int straightScore(final int[] dice, final int from, final int to) {
        return stream(dice).distinct().sorted().toArray().length == 5 &&
               stream(dice).min().orElse(0) == from &&
               stream(dice).max().orElse(0) == to ? 30 : 0;
    }

    private int choiceScore(final int[] dice) {
        return stream(dice).sum();
    }

    private Map<Integer, Long> groupResults(final int[] dice) {
        return stream(dice).boxed().collect(groupingBy(identity(), counting()));
    }
}