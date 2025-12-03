import java.util.Arrays;

class LargestSeriesProductCalculator {
    private final int[] digArray;

    LargestSeriesProductCalculator(String inputNumber) {
        if (inputNumber == null || inputNumber.chars().anyMatch(c -> !Character.isDigit(c))) {
            throw new IllegalArgumentException("String to search may only contain digits.");
        }
        this.digArray = inputNumber.chars().map(c -> c - '0').toArray();
    }

    long calculateLargestProductForSeriesLength(int width) {
        if (width < 0) {
            throw new IllegalArgumentException("Series length must be non-negative.");
        }
        if (digArray.length < width) {
            throw new IllegalArgumentException("Series length must be less than or equal to the length of the string to search.");
        }
        if (width == 0) {
            return 1;
        }

        long maxProduct = 0;
        long currentProduct = 1;
        int zeroCount = 0;

        for (int i = 0; i < digArray.length; i++) {
            if (digArray[i] == 0) {
                zeroCount++;
            } else {
                currentProduct *= digArray[i];
            }

            if (i >= width) {
                if (digArray[i - width] == 0) {
                    zeroCount--;
                } else {
                    currentProduct /= digArray[i - width];
                }
            }

            if (zeroCount == 0 && i >= width - 1) {
                maxProduct = Math.max(maxProduct, currentProduct);
            }
        }

        return maxProduct;
    }
}