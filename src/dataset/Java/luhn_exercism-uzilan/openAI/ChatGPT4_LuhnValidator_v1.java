class LuhnValidator {

    boolean isValid(String candidate) {
        String noSpaces = candidate.replace(" ", "");

        if (noSpaces.length() <= 1 || !noSpaces.chars().allMatch(Character::isDigit)) {
            return false;
        }

        int sum = 0;
        boolean shouldDouble = false;

        for (int i = noSpaces.length() - 1; i >= 0; i--) {
            int digit = noSpaces.charAt(i) - '0';
            if (shouldDouble) {
                digit *= 2;
                if (digit > 9) {
                    digit -= 9;
                }
            }
            sum += digit;
            shouldDouble = !shouldDouble;
        }

        return sum % 10 == 0;
    }
}