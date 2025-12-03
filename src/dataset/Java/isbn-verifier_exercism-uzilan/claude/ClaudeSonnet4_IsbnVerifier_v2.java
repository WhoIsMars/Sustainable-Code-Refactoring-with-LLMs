class IsbnVerifier {

    boolean isValid(String stringToVerify) {
        String cleaned = stringToVerify.replace("-", "");
        
        if (cleaned.length() != 10) {
            return false;
        }
        
        int sum = 0;
        for (int i = 0; i < 9; i++) {
            char c = cleaned.charAt(i);
            if (c < '0' || c > '9') {
                return false;
            }
            sum += (c - '0') * (10 - i);
        }
        
        char lastChar = cleaned.charAt(9);
        if (lastChar == 'X') {
            sum += 10;
        } else if (lastChar >= '0' && lastChar <= '9') {
            sum += (lastChar - '0');
        } else {
            return false;
        }
        
        return sum % 11 == 0;
    }
}