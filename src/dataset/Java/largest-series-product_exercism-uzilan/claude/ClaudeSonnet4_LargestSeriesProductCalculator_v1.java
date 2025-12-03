import java.util.function.IntUnaryOperator;

class LargestSeriesProductCalculator {

    private int[] numbers;

    LargestSeriesProductCalculator(String inputNumber) {
        if (!inputNumber.matches("\\d*")) {
            throw new IllegalArgumentException("String to search may only contain digits.");
        }

        this.numbers = new int[inputNumber.length()];
        for (int i = 0; i < inputNumber.length(); i++) {
            this.numbers[i] = inputNumber.charAt(i) - '0';
        }
    }

    long calculateLargestProductForSeriesLength(int numberOfDigits) {
        if (numberOfDigits > numbers.length) {
            throw new IllegalArgumentException(
                    "Series length must be less than or equal to the length of the string to search.");
        }

        if (numberOfDigits < 0) {
            throw new IllegalArgumentException("Series length must be non-negative.");
        }

        if (numberOfDigits == 0) {
            return 1;
        }

        long maxProduct = 0;
        final int noOfSeries = numbers.length - numberOfDigits + 1;

        for (int i = 0; i < noOfSeries; i++) {
            long product = 1;
            for (int j = 0; j < numberOfDigits; j++) {
                product *= numbers[i + j];
                if (product == 0) break; // Early exit if zero found
            }
            if (product > maxProduct) {
                maxProduct = product;
            }
        }

        return maxProduct;
    }

    private IntUnaryOperator calculateSerieProduct(int numberOfDigits) {
        return index -> {
            long product = 1;
            for (int i = 0; i < numberOfDigits; i++) {
                product *= numbers[index + i];
            }
            return (int) product;
        };
    }
}