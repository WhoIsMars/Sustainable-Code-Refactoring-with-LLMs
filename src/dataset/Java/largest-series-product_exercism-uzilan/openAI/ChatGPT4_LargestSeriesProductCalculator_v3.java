import java.util.List;
import java.util.stream.Collectors;

class LargestSeriesProductCalculator {

    private final List<Integer> numbers;

    LargestSeriesProductCalculator(String inputNumber) {
        if (!inputNumber.matches("\\d*")) {
            throw new IllegalArgumentException("String to search may only contain digits.");
        }

        this.numbers = inputNumber.chars()
                .map(Character::getNumericValue)
                .boxed()
                .toList();
    }

    long calculateLargestProductForSeriesLength(int numberOfDigits) {
        if (numberOfDigits > numbers.size()) {
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
        long currentProduct = 1;
        int zeroCount = 0;

        for (int i = 0; i < numbers.size(); i++) {
            int currentNum = numbers.get(i);

            if (currentNum == 0) {
                zeroCount++;
            } else {
                currentProduct *= currentNum;
            }

            if (i >= numberOfDigits) {
                int outgoingNum = numbers.get(i - numberOfDigits);
                if (outgoingNum == 0) {
                    zeroCount--;
                } else {
                    currentProduct /= outgoingNum;
                }
            }

            if (zeroCount == 0 && i >= numberOfDigits - 1) {
                maxProduct = Math.max(maxProduct, currentProduct);
            }
        }

        return maxProduct;
    }
}