import java.util.stream.IntStream;
import java.util.Arrays;

class SumOfMultiples {

    private final int NUMBER;
    private final int[] SET;

    SumOfMultiples(int number, int[] set) {
        this.NUMBER = number;
        this.SET = Arrays.stream(set).filter(x -> x > 0).toArray();
    }

    public int getSum() {
        return IntStream.range(1, NUMBER)
                .filter(candidate -> Arrays.stream(SET).anyMatch(divisor -> candidate % divisor == 0))
                .distinct()
                .sum();
    }
}