class LuhnValidator {

    boolean isValid(String candidate) {
        String noSpaces = candidate.replace(" ", "");

        if (noSpaces.length() <= 1 || !noSpaces.matches("\\d+")) {
            return false;
        }

        int sum = 0;
        boolean doubleDigit = false;

        for (int i = noSpaces.length() - 1; i >= 0; i--) {
            int digit = noSpaces.charAt(i) - '0';
            if (doubleDigit) {
                digit *= 2;
                if (digit > 9) {
                    digit -= 9;
                }
            }
            sum += digit;
            doubleDigit = !doubleDigit;
        }

        return sum % 10 == 0;
    }
}