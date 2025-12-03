class ArmstrongNumbers {

    boolean isArmstrongNumber(int numberToCheck) {
        String numberString = Integer.toString(numberToCheck);
        int numberOfDigits = numberString.length();
        int sum = 0;
        for (int i = 0; i < numberOfDigits; i++) {
            int digit = numberString.charAt(i) - '0';
            int power = 1;
            for (int j = 0; j < numberOfDigits; j++) {
                power *= digit;
            }
            sum += power;
        }
        return sum == numberToCheck;
    }
}