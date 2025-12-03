class LuhnValidator {

    boolean isValid(String candidate) {
        String noSpaces = candidate.replaceAll(" ", "");

        if (noSpaces.length() <= 1 || !noSpaces.matches("\\d+")) {
            return false;
        }

        int sum = 0;
        boolean doubleNext = false;

        for (int i = noSpaces.length() - 1; i >= 0; i--) {
            int digit = noSpaces.charAt(i) - '0';

            if (doubleNext) {
                digit *= 2;
                if (digit > 9) {
                    digit -= 9;
                }
            }

            sum += digit;
            doubleNext = !doubleNext;
        }

        return sum % 10 == 0;
    }
}