import java.util.Arrays;

class SumOfMultiples {

    private final int sum;

    SumOfMultiples(int number, int[] set) {
        // Filter out zeros and duplicates, sort for early termination
        int[] filteredSet = Arrays.stream(set)
                .filter(i -> i > 0)
                .distinct()
                .sorted()
                .toArray();
        
        sum = calculateSum(number, filteredSet);
    }

    int getSum() {
        return sum;
    }

    private int calculateSum(int number, int[] set) {
        if (set.length == 0) return 0;
        
        int sum = 0;
        for (int i = 1; i < number; i++) {
            if (isMultiple(i, set)) {
                sum += i;
            }
        }
        return sum;
    }

    private boolean isMultiple(int number, int[] set) {
        for (int divisor : set) {
            if (divisor > number) break; // Early termination since set is sorted
            if (number % divisor == 0) {
                return true;
            }
        }
        return false;
    }
}