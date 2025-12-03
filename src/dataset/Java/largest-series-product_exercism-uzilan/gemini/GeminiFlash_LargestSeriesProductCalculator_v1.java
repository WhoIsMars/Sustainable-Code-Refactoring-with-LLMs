import java.util.List;
import java.util.ArrayList;

class LargestSeriesProductCalculator {

    private final int[] numbers;

    LargestSeriesProductCalculator(String inputNumber) {
        if (!inputNumber.matches("\\d*")) {
            throw new IllegalArgumentException("String to search may only contain digits.");
        }

        this.numbers = new int[inputNumber.length()];
        for (int i = 0; i < inputNumber.length(); i++) {
            this.numbers[i] = Character.getNumericValue(inputNumber.charAt(i));
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
        for (int i = 0; i <= numbers.length - numberOfDigits; i++) {
            long currentProduct = 1;
            for (int j = 0; j < numberOfDigits; j++) {
                currentProduct *= numbers[i + j];
            }
            if (currentProduct > maxProduct) {
                maxProduct = currentProduct;
            }
        }
        return maxProduct;
    }
}