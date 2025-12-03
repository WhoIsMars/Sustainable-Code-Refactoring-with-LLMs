import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

class SumOfMultiples {

    private final int sum;

    SumOfMultiples(int number, int[] set) {
        this.sum = calculateSum(number, set);
    }

    int getSum() {
        return sum;
    }

    private int calculateSum(int number, int[] set) {
        Set<Integer> multiples = new HashSet<>();
        for (int factor : set) {
            if (factor == 0) continue;
            for (int i = factor; i < number; i += factor) {
                multiples.add(i);
            }
        }
        int sum = 0;
        for (int multiple : multiples) {
            sum += multiple;
        }
        return sum;
    }
}