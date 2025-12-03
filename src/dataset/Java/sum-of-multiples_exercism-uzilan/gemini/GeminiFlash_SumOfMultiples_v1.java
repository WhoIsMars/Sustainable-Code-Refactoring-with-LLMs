import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

class SumOfMultiples {

    private final int sum;

    SumOfMultiples(int number, int[] set) {
        this.sum = calculateSum(number, set);
    }

    private int calculateSum(int number, int[] set) {
        if (number <= 0 || set == null || set.length == 0) {
            return 0;
        }

        Set<Integer> multiples = new HashSet<>();
        for (int factor : set) {
            if (factor == 0) continue; // Skip zero to avoid division by zero

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


    int getSum() {
        return sum;
    }
}