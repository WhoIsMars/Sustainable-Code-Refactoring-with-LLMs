class IsbnVerifier {

    boolean isValid(String stringToVerify) {
        if (stringToVerify == null || stringToVerify.length() < 10) return false;

        int checksum = 0, multiplier = 10, digit;
        boolean hasX = false;

        for (int i = 0, len = stringToVerify.length(); i < len; i++) {
            char c = stringToVerify.charAt(i);

            if (c == 'X') {
                if (i != 9 || hasX) return false;
                digit = 10;
                hasX = true;
            } else if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else if (c == '-' || c == ' ') {
                continue;
            } else {
                return false;
            }

            if (multiplier > 0) {
                checksum += digit * multiplier--;
            }
        }

        return multiplier == 0 && checksum % 11 == 0;
    }
}