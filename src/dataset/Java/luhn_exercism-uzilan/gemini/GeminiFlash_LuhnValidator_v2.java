class LuhnValidator {

    boolean isValid(String candidate) {
        String noSpaces = candidate.replaceAll(" ", "");
        int len = noSpaces.length();

        if (len <= 1) {
            return false;
        }

        int sum = 0;
        boolean alternate = false;

        for (int i = len - 1; i >= 0; i--) {
            char c = noSpaces.charAt(i);
            if (!Character.isDigit(c)) {
                return false;
            }
            int n = c - '0';

            if (alternate) {
                n *= 2;
                if (n > 9) {
                    n -= 9;
                }
            }
            sum += n;
            alternate = !alternate;
        }

        return sum % 10 == 0;
    }
}