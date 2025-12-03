class LargestSeriesProductCalculator {
    private final int[] digArray;

    LargestSeriesProductCalculator(String inputNumber) {
        if (inputNumber == null) {
            throw new IllegalArgumentException("Input cannot be null.");
        }

        this.digArray = new int[inputNumber.length()];
        for (int i = 0; i < inputNumber.length(); i++) {
            char c = inputNumber.charAt(i);
            if (!Character.isDigit(c)) {
                throw new IllegalArgumentException("String to search may only contain digits.");
            }
            digArray[i] = c - '0';
        }
    }

    long calculateLargestProductForSeriesLength(int width) {
        if (digArray.length < width) {
            throw new IllegalArgumentException("Series length must be less than or equal to the length of the string to search.");
        } else if (width < 0){
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