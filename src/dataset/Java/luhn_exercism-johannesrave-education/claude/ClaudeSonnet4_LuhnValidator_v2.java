class LuhnValidator {

    boolean isValid(String candidate) {
        if (candidate.length() < 2) return false;
        
        int sum = 0;
        int digitCount = 0;
        boolean isEvenPosition = false;
        
        for (int i = candidate.length() - 1; i >= 0; i--) {
            char c = candidate.charAt(i);
            
            if (c == ' ') continue;
            
            if (c < '0' || c > '9') return false;
            
            int n = c - '0';
            digitCount++;
            
            if (isEvenPosition) {
                n *= 2;
                if (n > 9) n -= 9;
            }
            
            sum += n;
            isEvenPosition = !isEvenPosition;
        }
        
        return digitCount >= 2 && sum % 10 == 0;
    }
}