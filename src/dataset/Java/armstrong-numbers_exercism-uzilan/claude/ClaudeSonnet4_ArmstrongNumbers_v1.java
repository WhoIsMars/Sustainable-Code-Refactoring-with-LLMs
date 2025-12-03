class ArmstrongNumbers {

    boolean isArmstrongNumber(int numberToCheck) {
        if (numberToCheck < 0) return false;
        
        int original = numberToCheck;
        int numDigits = 0;
        int temp = numberToCheck;
        
        // Count digits
        do {
            numDigits++;
            temp /= 10;
        } while (temp > 0);
        
        // Calculate sum of powers
        long sum = 0;
        temp = numberToCheck;
        while (temp > 0) {
            int digit = temp % 10;
            sum += pow(digit, numDigits);
            temp /= 10;
        }
        
        return sum == original;
    }
    
    private long pow(int base, int exponent) {
        long result = 1;
        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
        return result;
    }
}