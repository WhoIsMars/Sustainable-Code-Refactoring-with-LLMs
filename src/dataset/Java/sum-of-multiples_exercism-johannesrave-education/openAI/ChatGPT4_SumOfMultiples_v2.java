import java.util.HashSet;

class SumOfMultiples {

    private final int NUMBER;
    private final int[] SET;

    SumOfMultiples(int number, int[] set) {
        this.NUMBER = number;
        this.SET = set;
    }

    public int getSum() {
        boolean[] isMultiple = new boolean[NUMBER];
        int sum = 0;

        for (int divisor : SET) {
            if (divisor == 0) {
                continue;
            }
            for (int multiple = divisor; multiple < NUMBER; multiple += divisor) {
                if (!isMultiple[multiple]) {
                    isMultiple[multiple] = true;
                    sum += multiple;
                }
            }
        }

        return sum;
    }
}