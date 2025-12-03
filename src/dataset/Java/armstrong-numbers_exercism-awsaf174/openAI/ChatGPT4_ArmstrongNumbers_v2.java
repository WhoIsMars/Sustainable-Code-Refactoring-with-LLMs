class ArmstrongNumbers {

    boolean isArmstrongNumber(int numberToCheck) {
        int sum = 0, temp = numberToCheck, digits = (int) Math.log10(numberToCheck) + 1;
        while (temp != 0) {
            int digit = temp % 10;
            sum += Math.pow(digit, digits);
            temp /= 10;
        }
        return sum == numberToCheck;
    }
}