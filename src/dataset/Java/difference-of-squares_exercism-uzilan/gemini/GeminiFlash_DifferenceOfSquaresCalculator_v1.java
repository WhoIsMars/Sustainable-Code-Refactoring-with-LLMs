class DifferenceOfSquaresCalculator {

    int computeSquareOfSumTo(int input) {
        long sum = (long) input * (input + 1) / 2;
        return (int) (sum * sum);
    }

    int computeSumOfSquaresTo(int input) {
        return (int) ((long) input * (input + 1) * (2 * input + 1) / 6);
    }

    int computeDifferenceOfSquares(int input) {
        return computeSquareOfSumTo(input) - computeSumOfSquaresTo(input);
    }
}