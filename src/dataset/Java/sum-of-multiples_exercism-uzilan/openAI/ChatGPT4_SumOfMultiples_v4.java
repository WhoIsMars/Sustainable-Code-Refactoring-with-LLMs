import java.util.HashSet;
import java.util.Set;

class SumOfMultiples {

    private final int sum;

    SumOfMultiples(int number, int[] set) {
        sum = calculateSum(number, set);
    }

    int getSum() {
        return sum;
    }

    private int calculateSum(int number, int[] set) {
        Set<Integer> multiples = new HashSet<>();
        for (int i : set) {
            if (i == 0) continue;
            for (int j = i; j < number; j += i) {
                multiples.add(j);
            }
        }
        return multiples.stream().mapToInt(Integer::intValue).sum();
    }
}