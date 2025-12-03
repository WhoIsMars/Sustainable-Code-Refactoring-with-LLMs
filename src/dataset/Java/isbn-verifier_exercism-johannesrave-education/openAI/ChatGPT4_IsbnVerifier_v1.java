class IsbnVerifier {

    boolean isValid(String stringToVerify) {
        if (stringToVerify == null || stringToVerify.length() < 10) return false;

        int checksum = 0, count = 0;
        for (int i = 0; i < stringToVerify.length(); i++) {
            char ch = stringToVerify.charAt(i);
            if (ch == '-') continue;

            if (count == 9 && ch == 'X') {
                checksum += 10;
                count++;
            } else if (Character.isDigit(ch)) {
                checksum += (ch - '0') * (10 - count);
                count++;
            } else {
                return false;
            }

            if (count > 10) return false;
        }
        return count == 10 && checksum % 11 == 0;
    }
}