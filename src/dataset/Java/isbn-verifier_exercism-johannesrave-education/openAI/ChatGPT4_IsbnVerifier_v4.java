class IsbnVerifier {

    boolean isValid(String stringToVerify) {
        if (stringToVerify == null || stringToVerify.length() < 10) return false;

        int checksum = 0, multiplier = 10, digit;
        boolean hasX = false;

        for (int i = 0, len = stringToVerify.length(); i < len; i++) {
            char ch = stringToVerify.charAt(i);

            if (ch == 'X') {
                if (i != len - 1 || hasX) return false;
                digit = 10;
                hasX = true;
            } else if (ch >= '0' && ch <= '9') {
                digit = ch - '0';
            } else if (ch == '-' || ch == ' ') {
                continue;
            } else {
                return false;
            }

            if (multiplier > 0) {
                checksum += digit * multiplier--;
            } else {
                return false;
            }
        }

        return multiplier == 0 && checksum % 11 == 0;
    }
}