import java.math.BigInteger;

class DifferenceOfSquaresCalculator {

    private static final BigInteger TWO = BigInteger.valueOf(2);
    private static final BigInteger THREE = BigInteger.valueOf(3);

    public static final int SQUARE_OF_SUMS_MAX = 304;
    public static final int SUM_OF_SQUARES_MAX = 1024;
    public static final int DIFFERENCE_OF_SQUARES_MAX = 305;

    public static int computeSquareOfSumTo(int n) {
        if (n > SQUARE_OF_SUMS_MAX) {
            System.err.printf("Overflow occurred for %d. Use computeSquareOfSumTo(BigInteger b) instead.%n", n);
            return -1;
        }
        int sum = n * (n + 1) / 2;
        return sum * sum;
    }

    public static BigInteger computeSquareOfSumTo(BigInteger b) {
        BigInteger sum = b.multiply(b.add(BigInteger.ONE)).divide(TWO);
        return sum.multiply(sum);
    }

    public static int computeSumOfSquaresTo(int n) {
        if (n > SUM_OF_SQUARES_MAX) {
            System.err.printf("Overflow occurred for %d. Use computeSumOfSquaresTo(BigInteger b) instead.%n", n);
            return -1;
        }
        return n * (n + 1) * (2 * n + 1) / 6;
    }

    public static BigInteger computeSumOfSquaresTo(BigInteger b) {
        return b.multiply(b.add(BigInteger.ONE))
                .multiply(b.multiply(TWO).add(BigInteger.ONE))
                .divide(BigInteger.valueOf(6));
    }

    public static int computeDifferenceOfSquares(int n) {
        if (n > DIFFERENCE_OF_SQUARES_MAX) {
            System.err.printf("Overflow occurred for %d. Use computeDifferenceOfSquares(BigInteger b) instead.%n", n);
            return -1;
        }
        return computeSquareOfSumTo(n) - computeSumOfSquaresTo(n);
    }

    public static BigInteger computeDifferenceOfSquares(BigInteger b) {
        return computeSquareOfSumTo(b).subtract(computeSumOfSquaresTo(b));
    }

    public static BigInteger BI(int n) {
        return BigInteger.valueOf(n);
    }

    static void findMaxima() {
        findMaxForMethod("computeSquareOfSumTo", DifferenceOfSquaresCalculator::computeSquareOfSumTo);
        findMaxForMethod("computeSumOfSquaresTo", DifferenceOfSquaresCalculator::computeSumOfSquaresTo);
        findMaxForMethod("computeDifferenceOfSquares", DifferenceOfSquaresCalculator::computeDifferenceOfSquares);
    }

    private static void findMaxForMethod(String methodName, java.util.function.Function<Integer, Integer> method) {
        System.out.printf("%n%s%n", methodName);
        int lastResult = 1, i = 1;
        while (lastResult > 0) {
            i++;
            lastResult = method.apply(i);
        }
        System.out.printf("An overflow happened at %d%n", i);
        System.out.println(method.apply(i - 1));
        System.out.println(method.apply(i));
        System.out.println(method.apply(i + 1));
    }
}