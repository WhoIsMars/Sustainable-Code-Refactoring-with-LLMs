class ArmstrongNumbers {

    boolean isArmstrongNumber(int numberToCheck) {
        if (numberToCheck < 0) {
            return false;
        }

        int num = numberToCheck;
        int sum = 0;
        int digits = 0;
        int temp = numberToCheck;

        while (temp > 0) {
            digits++;
            temp /= 10;
        }

        temp = numberToCheck;
        while (temp > 0) {
            int digit = temp % 10;
            sum += Math.pow(digit, digits);
            temp /= 10;
        }

        return sum == numberToCheck;
    }
}