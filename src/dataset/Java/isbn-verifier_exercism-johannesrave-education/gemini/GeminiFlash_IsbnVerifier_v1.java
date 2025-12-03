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
        for (int i = 0; i < 9; i++) {
            char c = isbn.charAt(i);
            if (!Character.isDigit(c)) return false;
            checksum += (c - '0') * (10 - i);
        }

        char lastChar = isbn.charAt(9);
        if (lastChar == 'X') {
            checksum += 10;
        } else if (Character.isDigit(lastChar)) {
            checksum += (lastChar - '0');
        } else {
            return false;
        }

        return checksum % 11 == 0;
    }
}