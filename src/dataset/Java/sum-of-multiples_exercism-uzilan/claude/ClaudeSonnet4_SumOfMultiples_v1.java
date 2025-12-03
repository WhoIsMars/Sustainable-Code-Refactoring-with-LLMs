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
        
        if (filteredSet.length == 0) {
            sum = 0;
            return;
        }
        
        int total = 0;
        for (int i = 1; i < number; i++) {
            if (hasMultiple(i, filteredSet)) {
                total += i;
            }
        }
        sum = total;
    }

    int getSum() {
        return sum;
    }

    private boolean hasMultiple(int number, int[] set) {
        for (int divisor : set) {
            if (divisor > number) {
                break; // Early termination since array is sorted
            }
            if (number % divisor == 0) {
                return true;
            }
        }
        return false;
    }
}