class ArmstrongNumbers {

    boolean isArmstrongNumber(int numberToCheck) {
        int temp = numberToCheck;
        int digits = 0;
        int sum = 0;

        // Calculate the number of digits
        while (temp != 0) {
            temp /= 10;
            digits++;
        }

        temp = numberToCheck; // Reset temp to the original number

        // Calculate the sum of digits raised to the power of the number of digits
        while (temp != 0) {
            int digit = temp % 10;
            int power = 1;
            for (int i = 0; i < digits; i++) {
                power *= digit;
            }
            sum += power;
            temp /= 10;
        }

        // Check if the sum is equal to the original number
        return sum == numberToCheck;
    }
}