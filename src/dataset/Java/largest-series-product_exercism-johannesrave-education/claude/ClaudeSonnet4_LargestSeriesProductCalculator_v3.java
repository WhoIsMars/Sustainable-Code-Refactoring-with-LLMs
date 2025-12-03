import java.util.Arrays;

class LargestSeriesProductCalculator {
    private final int[] digArray;

    LargestSeriesProductCalculator(String inputNumber) {
        if (inputNumber.length() == 0) {
            this.digArray = new int[0];
            return;
        }
        
        this.digArray = new int[inputNumber.length()];
        for (int i = 0; i < inputNumber.length(); i++) {
            char c = inputNumber.charAt(i);
            if (c < '0' || c > '9') {
                throw new IllegalArgumentException("String to search may only contain digits.");
            }
            this.digArray[i] = c - '0';
        }
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
        
        for (int i = 0; i <= digArray.length - width; i++) {
            long product = 1;
            boolean hasZero = false;
            
            for (int j = i; j < i + width; j++) {
                if (digArray[j] == 0) {
                    hasZero = true;
                    break;
                }
                product *= digArray[j];
            }
            
            if (!hasZero && product > maxProduct) {
                maxProduct = product;
            }
        }
        
        return maxProduct;
    }
}