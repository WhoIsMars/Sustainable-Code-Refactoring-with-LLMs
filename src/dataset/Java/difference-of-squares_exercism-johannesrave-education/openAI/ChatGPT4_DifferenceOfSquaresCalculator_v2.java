import java.math.BigInteger;

class DifferenceOfSquaresCalculator {

    public static final int SQUARE_OF_SUMS_MAX = 304;
    public static final int SUM_OF_SQUARES_MAX = 1024;
    public static final int DIFFERENCE_OF_SQUARES_MAX = 305;

    public static int computeSquareOfSumTo(int n) {
        if (n > SQUARE_OF_SUMS_MAX) {
            System.err.println("Overflow occurred for n = " + n + ". Use computeSquareOfSumTo(BigInteger b) instead.");
            return -1;
        }
        int sum = n * (n + 1) / 2;
        return sum * sum;
    }

    public static BigInteger computeSquareOfSumTo(BigInteger b) {
        BigInteger sum = b.multiply(b.add(BigInteger.ONE)).divide(BigInteger.TWO);
        return sum.multiply(sum);
    }

    public static int computeSumOfSquaresTo(int n) {
        if (n > SUM_OF_SQUARES_MAX) {
            System.err.println("Overflow occurred for n = " + n + ". Use computeSumOfSquaresTo(BigInteger b) instead.");
            return -1;
        }
        return n * (n + 1) * (2 * n + 1) / 6;
    }

    public static BigInteger computeSumOfSquaresTo(BigInteger b) {
        return b.multiply(b.add(BigInteger.ONE))
                .multiply(b.multiply(BigInteger.TWO).add(BigInteger.ONE))
                .divide(BigInteger.valueOf(6));
    }

    public static int computeDifferenceOfSquares(int n) {
        if (n > DIFFERENCE_OF_SQUARES_MAX) {
            System.err.println("Overflow occurred for n = " + n + ". Use computeDifferenceOfSquares(BigInteger b) instead.");
            return -1;
        }
        int squareOfSum = computeSquareOfSumTo(n);
        int sumOfSquares = computeSumOfSquaresTo(n);
        return squareOfSum - sumOfSquares;
    }

    public static BigInteger computeDifferenceOfSquares(BigInteger b) {
        return computeSquareOfSumTo(b).subtract(computeSumOfSquaresTo(b));
    }

    // Utility method for BigInteger value creation
    private static BigInteger BI(int n) {
        return BigInteger.valueOf(n);
    }

    // Optimized utility to find maxima
    static void findMaxima() {
        System.out.println("\ncomputeSquareOfSumTo(i)");
        findMaxForMethod(DifferenceOfSquaresCalculator::computeSquareOfSumTo);

        System.out.println("\ncomputeSumOfSquaresTo(i)");
        findMaxForMethod(DifferenceOfSquaresCalculator::computeSumOfSquaresTo);

        System.out.println("\ncomputeDifferenceOfSquares(i)");
        findMaxForMethod(DifferenceOfSquaresCalculator::computeDifferenceOfSquares);
    }

    private static void findMaxForMethod(IntUnaryOperator method) {
        int lastResult = 1;
        int i = 1;
        while (lastResult > 0) {
            i++;
            lastResult = method.applyAsInt(i);
        }
        System.out.printf("An overflow happened at %d%n", i);
        System.out.println(method.applyAsInt(i - 1));
        System.out.println(method.applyAsInt(i));
        System.out.println(method.applyAsInt(i + 1));
    }

    @FunctionalInterface
    interface IntUnaryOperator {
        int applyAsInt(int operand);
    }
}