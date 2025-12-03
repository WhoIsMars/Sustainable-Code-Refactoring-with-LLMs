import java.util.Arrays;

class ArmstrongNumbers {

    boolean isArmstrongNumber(int numberToCheck) {
        if (numberToCheck < 0) return false;
        if (numberToCheck < 10) return true;
        
        int temp = numberToCheck;
        int digitCount = 0;
        while (temp > 0) {
            digitCount++;
            temp /= 10;
        }
        
        temp = numberToCheck;
        long sum = 0;
        while (temp > 0) {
            int digit = temp % 10;
            sum += pow(digit, digitCount);
            temp /= 10;
        }
        
        return sum == numberToCheck;
    }
    
    private long pow(int base, int exponent) {
        long result = 1;
        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
        return result;
    }
}