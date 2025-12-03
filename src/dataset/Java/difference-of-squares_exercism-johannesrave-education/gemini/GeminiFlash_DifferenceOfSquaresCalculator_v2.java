import java.math.BigInteger;

class DifferenceOfSquaresCalculator {

    public static final int SQUARE_OF_SUMS_MAX = 304;
    public static final int SUM_OF_SQUARES_MAX = 1024;
    public static final int DIFFERENCE_OF_SQUARES_MAX = 305;

    public static int computeSquareOfSumTo(int n) {
        if (n > SQUARE_OF_SUMS_MAX) {
            System.out.println("An overflow occured when computing for " + n);
            System.out.println("Please use computeSquareOfSumTo(BigInteger b) instead.");
            return -1;
        }
        long sum = (long)n * (n + 1) / 2;
        return (int)(sum * sum);
    }

    public static BigInteger computeSquareOfSumTo(BigInteger b) {
        BigInteger sum = b.add(BigInteger.ONE);
        sum = b.multiply(sum).divide(BigInteger.TWO);
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
        BigInteger nPlus1 = b.add(BigInteger.ONE);
        BigInteger twoNPlus1 = b.multiply(BigInteger.TWO).add(BigInteger.ONE);
        return b.multiply(nPlus1).multiply(twoNPlus1).divide(BigInteger.valueOf(6));
    }

    public static int computeDifferenceOfSquares(int n) {
        if (n > DIFFERENCE_OF_SQUARES_MAX) {
            System.out.println("An overflow occured when computing for " + n);
            System.out.println("Please use computeDifferenceOfSquares(BigInteger b) instead.");
            return -1;
        }
        long squareOfSum = (long)n * (n + 1) / 2;
        squareOfSum *= squareOfSum;
        long sumOfSquares = (long)n * (n + 1) * (2 * n + 1) / 6;
        return (int)(squareOfSum - sumOfSquares);
    }
    
    public static BigInteger computeDifferenceOfSquares(BigInteger b) {
        BigInteger squareOfSum = computeSquareOfSumTo(b);
        BigInteger sumOfSquares = computeSumOfSquaresTo(b);
        return squareOfSum.subtract(sumOfSquares);
    }
    
    private static final BigInteger TWO = BigInteger.valueOf(2);
    private static final BigInteger SIX = BigInteger.valueOf(6);

    // Shortened BigInteger.valueOf(n) to pseudoconstructor for better readability of formulae
    public static BigInteger BI(int n) {
        return BigInteger.valueOf(n);
    }
    // Just a utility class to find the allowed maximum for each of the methods. 
    // This could probably be improved but worked alright.
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