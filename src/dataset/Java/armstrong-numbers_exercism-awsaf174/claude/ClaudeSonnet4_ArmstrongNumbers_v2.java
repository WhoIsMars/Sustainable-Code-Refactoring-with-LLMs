class ArmstrongNumbers {

    boolean isArmstrongNumber(int numberToCheck) {
        if (numberToCheck < 0) return false;
        if (numberToCheck < 10) return true;
        
        int temp = numberToCheck;
        int digits = 0;
        
        // Count digits
        while (temp > 0) {
            temp /= 10;
            digits++;
        }
        
        temp = numberToCheck;
        long sum = 0;
        
        // Calculate sum of powers
        while (temp > 0) {
            int digit = temp % 10;
            sum += pow(digit, digits);
            temp /= 10;
        }
        
        return sum == numberToCheck;
    }
    
    private long pow(int base, int exp) {
        long result = 1;
        for (int i = 0; i < exp; i++) {
            result *= base;
        }
        return result;
    }
}