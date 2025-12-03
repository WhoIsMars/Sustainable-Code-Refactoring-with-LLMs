import java.util.Arrays;

class LargestSeriesProductCalculator {
    private final int[] digArray;

    LargestSeriesProductCalculator(String inputNumber) {
        if (inputNumber == null || inputNumber.chars().anyMatch(ch -> !Character.isDigit(ch))) {
            throw new IllegalArgumentException("String to search may only contain digits.");
        }
        this.digArray = inputNumber.chars().map(ch -> ch - '0').toArray();
    }

    long calculateLargestProductForSeriesLength(int width) {
        if (width < 0) {
            throw new IllegalArgumentException("Series length must be non-negative.");
        }
        if (digArray.length < width) {
            throw new IllegalArgumentException("Series length must be less than or equal to the length of the string to search.");
        }
        long maxProduct = 0;
        for (int i = 0; i <= digArray.length - width; i++) {
            long product = 1;
            for (int j = 0; j < width; j++) {
                product *= digArray[i + j];
            }
            maxProduct = Math.max(maxProduct, product);
        }
        return maxProduct;
    }
}