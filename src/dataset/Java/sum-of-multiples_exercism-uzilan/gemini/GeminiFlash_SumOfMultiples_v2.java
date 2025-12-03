import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.stream.IntStream;

class SumOfMultiples {

    private final int sum;

    SumOfMultiples(int number, int[] set) {
        this.sum = calculateSum(number, set);
    }

    private int calculateSum(int number, int[] set) {
        Set<Integer> multiples = new HashSet<>();
        for (int factor : set) {
            if (factor == 0) continue; // Avoid division by zero
            for (int i = factor; i < number; i += factor) {
                multiples.add(i);
            }
        }
        return multiples.stream().mapToInt(Integer::intValue).sum();
    }


    int getSum() {
        return sum;
    }
}