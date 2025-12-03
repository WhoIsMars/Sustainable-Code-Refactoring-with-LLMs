class ArmstrongNumbers {

    boolean isArmstrongNumber(int numberToCheck) {
        if (numberToCheck < 0) return false;
        
        int original = numberToCheck;
        int numDigits = 0;
        int temp = numberToCheck;
        
        // Count digits
        while (temp > 0) {
            numDigits++;
            temp /= 10;
        }
        
        // Calculate sum of powers
        int sum = 0;
        temp = numberToCheck;
        while (temp > 0) {
            int digit = temp % 10;
            sum += pow(digit, numDigits);
            temp /= 10;
        }
        
        return sum == original;
    }
    
    private int pow(int base, int exp) {
        int result = 1;
        for (int i = 0; i < exp; i++) {
            result *= base;
        }
        return result;
    }
}