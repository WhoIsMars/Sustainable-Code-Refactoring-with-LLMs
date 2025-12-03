import java.util.HashSet;
import java.util.Set;

class SumOfMultiples {

    private final int sum;

    SumOfMultiples(int number, int[] set) {
        Set<Integer> multiples = new HashSet<>();
        for (int i : set) {
            if (i > 0) {
                for (int j = i; j < number; j += i) {
                    multiples.add(j);
                }
            }
        }
        sum = multiples.stream().mapToInt(Integer::intValue).sum();
    }

    int getSum() {
        return sum;
    }
}