class IsbnVerifier {

    boolean isValid(String stringToVerify) {
        if (stringToVerify == null || stringToVerify.length() < 10) return false;
        
        int validChars = 0;
        int checksum = 0;
        boolean hasX = false;
        
        for (int i = 0; i < stringToVerify.length() && validChars < 10; i++) {
            char c = stringToVerify.charAt(i);
            if (c >= '0' && c <= '9') {
                checksum += (c - '0') * (10 - validChars);
                validChars++;
            } else if (c == 'X') {
                if (validChars == 9) {
                    checksum += 10;
                    validChars++;
                    hasX = true;
                } else {
                    return false;
                }
            }
        }
        
        return validChars == 10 && checksum % 11 == 0;
    }
}