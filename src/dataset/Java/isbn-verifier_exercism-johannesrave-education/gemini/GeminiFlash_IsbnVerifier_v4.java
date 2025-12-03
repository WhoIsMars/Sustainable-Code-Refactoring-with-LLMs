class IsbnVerifier {

    boolean isValid(String stringToVerify) {
        String isbn = stringToVerify.replaceAll("[^0-9X]", "");

        if (isbn.length() != 10) {
            return false;
        }

        if (isbn.indexOf('X') != -1 && isbn.charAt(9) != 'X') {
            return false;
        }

        int checksum = 0;
        for (int i = 0; i < 10; i++) {
            char c = isbn.charAt(i);
            if (c == 'X') {
                checksum += 10;
            } else {
                int digit = c - '0';
                checksum += digit * (10 - i);
            }
        }

        return checksum % 11 == 0;
    }
}