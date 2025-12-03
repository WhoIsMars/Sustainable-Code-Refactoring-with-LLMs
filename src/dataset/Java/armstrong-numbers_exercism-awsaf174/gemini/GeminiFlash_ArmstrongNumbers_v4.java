class ArmstrongNumbers {

    boolean isArmstrongNumber(int numberToCheck) {
        int numDigits = 0;
        int temp = numberToCheck;
        int sum = 0;

        if (numberToCheck < 0) {
            return false;
        }

        while (temp != 0) {
            numDigits++;
            temp /= 10;
        }

        temp = numberToCheck;
        while (temp != 0) {
            int digit = temp % 10;
            sum += Math.pow(digit, numDigits);
            temp /= 10;
        }

        return sum == numberToCheck;
    }
}