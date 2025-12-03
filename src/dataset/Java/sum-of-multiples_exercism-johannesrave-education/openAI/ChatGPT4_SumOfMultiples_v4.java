import java.util.HashSet;

class SumOfMultiples {

    private final int NUMBER;
    private final int[] SET;

    SumOfMultiples(int number, int[] set) {
        this.NUMBER = number;
        this.SET = set;
    }

    public int getSum() {
        HashSet<Integer> multiples = new HashSet<>();
        for (int divisor : SET) {
            if (divisor == 0) continue;
            for (int multiple = divisor; multiple < NUMBER; multiple += divisor) {
                multiples.add(multiple);
            }
        }
        return multiples.stream().mapToInt(Integer::intValue).sum();
    }
}