class IsbnVerifier {

    boolean isValid(String stringToVerify) {
        if (stringToVerify == null || stringToVerify.length() < 10) return false;
        
        int validChars = 0;
        int checksum = 0;
        
        for (int i = 0; i < stringToVerify.length(); i++) {
            char c = stringToVerify.charAt(i);
            
            if (c >= '0' && c <= '9') {
                if (validChars == 10) return false;
                checksum += (c - '0') * (10 - validChars);
                validChars++;
            } else if (c == 'X') {
                if (validChars != 9) return false;
                checksum += 10;
                validChars++;
            } else if (c != '-' && c != ' ') {
                return false;
            }
        }
        
        return validChars == 10 && checksum % 11 == 0;
    }
}