class IsbnVerifier {

    boolean isValid(String stringToVerify) {
        if (stringToVerify == null || stringToVerify.length() < 10) return false;
        
        int digitCount = 0;
        int checksum = 0;
        boolean hasX = false;
        
        for (int i = 0; i < stringToVerify.length() && digitCount < 10; i++) {
            char c = stringToVerify.charAt(i);
            if (c >= '0' && c <= '9') {
                checksum += (c - '0') * (10 - digitCount);
                digitCount++;
            } else if (c == 'X') {
                if (digitCount != 9) return false;
                checksum += 10;
                digitCount++;
                hasX = true;
            }
        }
        
        return digitCount == 10 && checksum % 11 == 0;
    }
}