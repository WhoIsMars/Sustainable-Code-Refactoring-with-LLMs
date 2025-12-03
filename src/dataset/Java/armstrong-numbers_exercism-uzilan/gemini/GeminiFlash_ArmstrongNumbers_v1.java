class ArmstrongNumbers {

    boolean isArmstrongNumber(int numberToCheck) {
        String numberStr = Integer.toString(numberToCheck);
        int numDigits = numberStr.length();
        int sum = 0;
        for (int i = 0; i < numDigits; i++) {
            int digit = numberStr.charAt(i) - '0';
            int power = 1;
            for (int j = 0; j < numDigits; j++) {
                power *= digit;
            }
            sum += power;
        }
        return sum == numberToCheck;
    }
}