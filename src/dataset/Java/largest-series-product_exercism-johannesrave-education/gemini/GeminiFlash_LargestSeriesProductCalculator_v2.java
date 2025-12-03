import java.util.Arrays;

class LargestSeriesProductCalculator {
    private final int[] digArray;

    LargestSeriesProductCalculator(String inputNumber) {
        if (inputNumber == null) {
            throw new IllegalArgumentException("Input cannot be null.");
        }
        this.digArray = (inputNumber.isEmpty()) ? new int[0] :
                inputNumber.chars()
                        .map(c -> {
                            if (!Character.isDigit(c)) {
                                throw new IllegalArgumentException("String to search may only contain digits.");
                            }
                            return c - '0';
                        })
                        .toArray();
    }

    long calculateLargestProductForSeriesLength(int width) {
        if (width > digArray.length) {
            throw new IllegalArgumentException("Series length must be less than or equal to the length of the string to search.");
        } else if (width < 0) {
            throw new IllegalArgumentException("Series length must be non-negative.");
        }

        if (width == 0) {
            return 1;
        }

        long maxProduct = 0;
        for (int i = 0; i <= digArray.length - width; i++) {
            long currentProduct = 1;
            for (int j = i; j < i + width; j++) {
                currentProduct *= digArray[j];
            }
            maxProduct = Math.max(maxProduct, currentProduct);
        }

        return maxProduct;
    }
}