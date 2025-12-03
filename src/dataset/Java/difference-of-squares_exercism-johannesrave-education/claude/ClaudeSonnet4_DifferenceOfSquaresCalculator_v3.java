import java.math.BigInteger;

class DifferenceOfSquaresCalculator {

    public static final int SQUARE_OF_SUMS_MAX = 304;
    public static final int SUM_OF_SQUARES_MAX = 1024;
    public static final int DIFFERENCE_OF_SQUARES_MAX = 305;
    
    private static final BigInteger TWO = BigInteger.valueOf(2);
    private static final BigInteger SIX = BigInteger.valueOf(6);

    public static int computeSquareOfSumTo(int n) {
        if (n > SQUARE_OF_SUMS_MAX) {
            System.out.println("An overflow occured when computing for " + n);
            System.out.println("Please use computeSquareOfSumTo(BigInteger b) instead.");
            return -1;
        }
        int sum = (n * (n + 1)) >> 1;
        return sum * sum;
    }

    public static BigInteger computeSquareOfSumTo(BigInteger b) {
        BigInteger sum = b.multiply(b.add(BigInteger.ONE)).shiftRight(1);
        return sum.multiply(sum);
    }

    public static int computeSumOfSquaresTo(int n) {
        if (n > SUM_OF_SQUARES_MAX) {
            System.out.println("An overflow occured when computing for " + n);
            System.out.println("Please use computeSumOfSquaresTo(BigInteger b) instead.");
            return -1;
        }
        return (n * (n + 1) * (2 * n + 1)) / 6;
    }

    public static BigInteger computeSumOfSquaresTo(BigInteger b) {
        BigInteger bPlusOne = b.add(BigInteger.ONE);
        return b.multiply(bPlusOne).multiply(TWO.multiply(b).add(BigInteger.ONE)).divide(SIX);
    }

    public static int computeDifferenceOfSquares(int n) {
        if (n > DIFFERENCE_OF_SQUARES_MAX) {
            System.out.println("An overflow occured when computing for " + n);
            System.out.println("Please use computeDifferenceOfSquares(BigInteger b) instead.");
            return -1;
        }
        int sum = (n * (n + 1)) >> 1;
        int squareOfSum = sum * sum;
        int sumOfSquares = (n * (n + 1) * (2 * n + 1)) / 6;
        return squareOfSum - sumOfSquares;
    }
    
    public static BigInteger computeDifferenceOfSquares(BigInteger b) {
        BigInteger bPlusOne = b.add(BigInteger.ONE);
        BigInteger sum = b.multiply(bPlusOne).shiftRight(1);
        BigInteger squareOfSum = sum.multiply(sum);
        BigInteger sumOfSquares = b.multiply(bPlusOne).multiply(TWO.multiply(b).add(BigInteger.ONE)).divide(SIX);
        return squareOfSum.subtract(sumOfSquares);
    }
    
    public static BigInteger BI(int n) {
        return BigInteger.valueOf(n);
    }
    
    static void findMaxima(){
        System.out.println("\ncomputeSquareOfSumTo(i)");
        int lastResult = 1;
        int i = 1;
        while (lastResult > 0){
            i++;
            lastResult = computeSquareOfSumTo(i);
        }
        System.out.println("An overflow happened at " + i);
        System.out.println(computeSquareOfSumTo(i-1));
        System.out.println(computeSquareOfSumTo(i));
        System.out.println(computeSquareOfSumTo(i+1));

        System.out.println("\ncomputeSumOfSquaresTo(i)");
        lastResult = 1;
        i = 1;
        while (lastResult > 0){
            i++;
            lastResult = computeSumOfSquaresTo(i);
        }
        System.out.println("An overflow happened at " + i);
        System.out.println(computeSumOfSquaresTo(i-1));
        System.out.println(computeSumOfSquaresTo(i));
        System.out.println(computeSumOfSquaresTo(i+1));

        System.out.println("\ncomputeDifferenceOfSquares(i)");
        lastResult = 1;
        i = 1;
        while (lastResult > 0){
            i++;
            lastResult = computeDifferenceOfSquares(i);
        }
        System.out.println("An overflow happened at " + i);
        System.out.println(computeDifferenceOfSquares(i-1));
        System.out.println(computeDifferenceOfSquares(i));
        System.out.println(computeDifferenceOfSquares(i+1));
    }
}