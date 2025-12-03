import java.util.Arrays;
import java.util.stream.IntStream;

class SumOfMultiples {

    private final int NUMBER;
    private final int[] SET;

    SumOfMultiples(int number, int[] set) {
        this.NUMBER = number;
        this.SET = Arrays.stream(set).filter(x -> x > 0).toArray();
    }

    public int getSum() {
        return IntStream.range(1, NUMBER)
                .filter(num -> Arrays.stream(SET).anyMatch(divisor -> num % divisor == 0))
                .distinct()
                .sum();
    }
}