class ArmstrongNumbers {

    boolean isArmstrongNumber(int numberToCheck) {
        if (numberToCheck < 0) return false;
        
        int temp = numberToCheck;
        int digitCount = 0;
        
        while (temp > 0) {
            digitCount++;
            temp /= 10;
        }
        
        temp = numberToCheck;
        int sum = 0;
        
        while (temp > 0) {
            int digit = temp % 10;
            sum += pow(digit, digitCount);
            temp /= 10;
        }
        
        return sum == numberToCheck;
    }
    
    private int pow(int base, int exponent) {
        int result = 1;
        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
        return result;
    }
}