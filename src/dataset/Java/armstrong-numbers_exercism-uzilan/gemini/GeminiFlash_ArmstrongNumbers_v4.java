class ArmstrongNumbers {

    boolean isArmstrongNumber(int numberToCheck) {
        String numberString = Integer.toString(numberToCheck);
        int numDigits = numberString.length();
        int sum = 0;
        for (int i = 0; i < numDigits; i++) {
            int digit = numberString.charAt(i) - '0';
            int power = 1;
            for (int j = 0; j < numDigits; j++) {
                power *= digit;
            }
            sum += power;
            if (sum > numberToCheck) {
                return false;
            }
        }
        return sum == numberToCheck;
    }
}