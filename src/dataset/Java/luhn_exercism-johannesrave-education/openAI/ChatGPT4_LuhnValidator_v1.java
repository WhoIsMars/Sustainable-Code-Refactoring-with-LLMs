class LuhnValidator {

    boolean isValid(String candidate) {
        String trimmed = candidate.replaceAll("\\s+", "");
        int length = trimmed.length();
        
        if (length < 2) return false;

        int sum = 0;
        boolean doubleDigit = false;

        for (int i = length - 1; i >= 0; i--) {
            char c = trimmed.charAt(i);
            if (c < '0' || c > '9') return false;

            int n = c - '0';
            if (doubleDigit) {
                n *= 2;
                if (n > 9) n -= 9;
            }
            sum += n;
            doubleDigit = !doubleDigit;
        }

        return sum % 10 == 0;
    }

}