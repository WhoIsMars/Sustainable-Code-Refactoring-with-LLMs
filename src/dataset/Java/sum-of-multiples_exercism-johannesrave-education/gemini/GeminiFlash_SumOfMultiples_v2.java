import java.util.HashSet;
import java.util.Arrays;

class SumOfMultiples {

    private final int NUMBER;
    private final int[] SET;

    SumOfMultiples(int number, int[] set) {
        this.NUMBER = number;
        this.SET = Arrays.stream(set).filter(x -> x > 0).toArray(); // Filter out 0 and negative numbers early
    }

    public int getSum() {
        HashSet<Integer> multiples = new HashSet<>(); // Initialize here for better memory management
        int sum = 0;

        for (int divisor : SET) {
            if (divisor >= NUMBER) continue; // Optimization: Skip divisors greater than or equal to NUMBER

            for (int multiple = divisor; multiple < NUMBER; multiple += divisor) {
                multiples.add(multiple);
            }
        }

        return multiples.stream().mapToInt(Integer::intValue).sum(); // Efficient sum calculation
    }
}