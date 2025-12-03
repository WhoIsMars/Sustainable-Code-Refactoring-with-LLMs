class IsbnVerifier {

    boolean isValid(String stringToVerify) {
        if (stringToVerify == null || stringToVerify.length() < 10) return false;

        int checksum = 0, multiplier = 10, digit;
        boolean hasX = false;

        for (int i = 0, count = 0; i < stringToVerify.length() && count < 10; i++) {
            char c = stringToVerify.charAt(i);

            if (c == '-') continue;

            if (c == 'X') {
                if (count != 9) return false;
                digit = 10;
                hasX = true;
            } else if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else {
                return false;
            }

            checksum += digit * multiplier--;
            count++;
        }

        return !hasX || checksum % 11 == 0;
    }
}