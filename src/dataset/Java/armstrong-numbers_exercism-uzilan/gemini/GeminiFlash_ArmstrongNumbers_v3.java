import java.util.Arrays;

class ArmstrongNumbers {

    boolean isArmstrongNumber(int numberToCheck) {
        String numberString = String.valueOf(numberToCheck);
        int numDigits = numberString.length();
        int sum = 0;
        int temp = numberToCheck;

        while (temp > 0) {
            int digit = temp % 10;
            sum += power(digit, numDigits);
            temp /= 10;
        }

        return sum == numberToCheck;
    }

    private int power(int base, int exponent) {
        int result = 1;
        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
        return result;
    }
}