import java.util.Arrays;

class SumOfMultiples {

    private final int sum;

    SumOfMultiples(int number, int[] set) {
        if (set == null || set.length == 0 || number <= 1) {
            sum = 0;
            return;
        }
        
        int[] validSet = Arrays.stream(set)
                .filter(i -> i > 0 && i < number)
                .distinct()
                .toArray();
        
        if (validSet.length == 0) {
            sum = 0;
            return;
        }
        
        boolean[] isMultiple = new boolean[number];
        
        for (int divisor : validSet) {
            for (int multiple = divisor; multiple < number; multiple += divisor) {
                isMultiple[multiple] = true;
            }
        }
        
        int total = 0;
        for (int i = 1; i < number; i++) {
            if (isMultiple[i]) {
                total += i;
            }
        }
        
        sum = total;
    }

    int getSum() {
        return sum;
    }
}