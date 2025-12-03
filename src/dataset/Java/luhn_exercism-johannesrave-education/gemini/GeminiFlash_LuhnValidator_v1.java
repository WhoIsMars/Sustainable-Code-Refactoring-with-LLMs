class LuhnValidator {

    boolean isValid(String candidate) {
        String cleanedCandidate = candidate.replaceAll("\\s+", "");
        int length = cleanedCandidate.length();

        if (length < 2) {
            return false;
        }

        int sum = 0;
        for (int i = length - 1; i >= 0; i--) {
            char c = cleanedCandidate.charAt(i);
            if (!Character.isDigit(c)) {
                return false;
            }

            int digit = c - '0';
            if ((length - i) % 2 == 0) {
                digit *= 2;
                if (digit > 9) {
                    digit -= 9;
                }
            }
            sum += digit;
        }

        return sum % 10 == 0;
    }
}