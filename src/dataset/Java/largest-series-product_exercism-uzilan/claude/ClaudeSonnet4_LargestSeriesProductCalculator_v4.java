import java.util.function.IntUnaryOperator;
import java.util.stream.IntStream;

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

        final int noOfSeries = numbers.length - numberOfDigits + 1;

        return IntStream.range(0, noOfSeries)
                .mapToLong(calculateSerieProduct(numberOfDigits))
                .max()
                .orElse(0);
    }

    private IntUnaryOperator calculateSerieProduct(int numberOfDigits) {
        return index -> {
            long product = 1;
            for (int i = index; i < index + numberOfDigits; i++) {
                product *= numbers[i];
                if (product == 0) {
                    break;
                }
            }
            return (int) product;
        };
    }
}