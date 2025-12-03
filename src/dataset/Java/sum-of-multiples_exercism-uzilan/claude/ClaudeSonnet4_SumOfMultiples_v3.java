import java.util.Arrays;
import java.util.function.IntPredicate;

class SumOfMultiples {

    private final int sum;

    SumOfMultiples(int number, int[] set) {
        if (set.length == 0 || number <= 1) {
            sum = 0;
            return;
        }
        
        int[] validSet = Arrays.stream(set)
                .filter(i -> i > 0 && i < number)
                .distinct()
                .sorted()
                .toArray();
        
        if (validSet.length == 0) {
            sum = 0;
            return;
        }
        
        sum = calculateSum(number, validSet);
    }

    int getSum() {
        return sum;
    }

    private IntPredicate hasMultiplies(int[] set) {
        return number -> {
            for (int i : set) {
                if (number % i == 0) {
                    return true;
                }
            }
            return false;
        };
    }
    
    private int calculateSum(int number, int[] set) {
        int total = 0;
        for (int i = 1; i < number; i++) {
            for (int divisor : set) {
                if (i % divisor == 0) {
                    total += i;
                    break;
                }
            }
        }
        return total;
    }
}